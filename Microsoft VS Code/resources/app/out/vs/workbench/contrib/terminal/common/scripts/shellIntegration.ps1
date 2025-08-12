# ---------------------------------------------------------------------------------------------
#   Copyright (c) Microsoft Corporation. All rights reserved.
#   Licensed under the MIT License. See License.txt in the project root for license information.
# ---------------------------------------------------------------------------------------------

# Prevent installing more than once per session
if (Test-Path variable:global:__VSCodeState.OriginalPrompt) {
	return;
}

# Disable shell integration when the language mode is restricted
if ($ExecutionContext.SessionState.LanguageMode -ne "FullLanguage") {
	return;
}

$Global:__VSCodeState = @{
	OriginalPrompt = $function:Prompt
	LastHistoryId = -1
	IsInExecution = $false
	EnvVarsToReport = @()
	Nonce = $null
	IsStable = $null
	IsWindows10 = $false
}

# Store the nonce in a regular variable and unset the environment variable. It's by design that
# anything that can execute PowerShell code can read the nonce, as it's basically impossible to hide
# in PowerShell. The most important thing is getting it out of the environment.
$Global:__VSCodeState.Nonce = $env:VSCODE_NONCE
$env:VSCODE_NONCE = $null

$Global:__VSCodeState.IsStable = $env:VSCODE_STABLE
$env:VSCODE_STABLE = $null

$__vscode_shell_env_reporting = $env:VSCODE_SHELL_ENV_REPORTING
$env:VSCODE_SHELL_ENV_REPORTING = $null
if ($__vscode_shell_env_reporting) {
	$Global:__VSCodeState.EnvVarsToReport = $__vscode_shell_env_reporting.Split(',')
}
Remove-Variable -Name __vscode_shell_env_reporting -ErrorAction SilentlyContinue

$osVersion = [System.Environment]::OSVersion.Version
$Global:__VSCodeState.IsWindows10 = $IsWindows -and $osVersion.Major -eq 10 -and $osVersion.Minor -eq 0 -and $osVersion.Build -lt 22000
Remove-Variable -Name osVersion -ErrorAction SilentlyContinue

if ($env:VSCODE_ENV_REPLACE) {
	$Split = $env:VSCODE_ENV_REPLACE.Split(":")
	foreach ($Item in $Split) {
		$Inner = $Item.Split('=', 2)
		[Environment]::SetEnvironmentVariable($Inner[0], $Inner[1].Replace('\x3a', ':'))
	}
	$env:VSCODE_ENV_REPLACE = $null
}
if ($env:VSCODE_ENV_PREPEND) {
	$Split = $env:VSCODE_ENV_PREPEND.Split(":")
	foreach ($Item in $Split) {
		$Inner = $Item.Split('=', 2)
		[Environment]::SetEnvironmentVariable($Inner[0], $Inner[1].Replace('\x3a', ':') + [Environment]::GetEnvironmentVariable($Inner[0]))
	}
	$env:VSCODE_ENV_PREPEND = $null
}
if ($env:VSCODE_ENV_APPEND) {
	$Split = $env:VSCODE_ENV_APPEND.Split(":")
	foreach ($Item in $Split) {
		$Inner = $Item.Split('=', 2)
		[Environment]::SetEnvironmentVariable($Inner[0], [Environment]::GetEnvironmentVariable($Inner[0]) + $Inner[1].Replace('\x3a', ':'))
	}
	$env:VSCODE_ENV_APPEND = $null
}

function Global:__VSCode-Escape-Value([string]$value) {
	# NOTE: In PowerShell v6.1+, this can be written `$value -replace '…', { … }` instead of `[regex]::Replace`.
	# Replace any non-alphanumeric characters.
	[regex]::Replace($value, "[$([char]0x00)-$([char]0x1f)\\\n;]", { param($match)
			# Encode the (ascii) matches as `\x<hex>`
			-Join (
				[System.Text.Encoding]::UTF8.GetBytes($match.Value) | ForEach-Object { '\x{0:x2}' -f $_ }
			)
		})
}

function Global:Prompt() {
	$FakeCode = [int]!$global:?
	# NOTE: We disable strict mode for the scope of this function because it unhelpfully throws an
	# error when $LastHistoryEntry is null, and is not otherwise useful.
	Set-StrictMode -Off
	$LastHistoryEntry = Get-History -Count 1
	$Result = ""
	# Skip finishing the command if the first command has not yet started or an execution has not
	# yet begun
	if ($Global:__VSCodeState.LastHistoryId -ne -1 -and ($Global:__VSCodeState.HasPSReadLine -eq $false -or $Global:__VSCodeState.IsInExecution -eq $true)) {
		$Global:__VSCodeState.IsInExecution = $false
		if ($LastHistoryEntry.Id -eq $Global:__VSCodeState.LastHistoryId) {
			# Don't provide a command line or exit code if there was no history entry (eg. ctrl+c, enter on no command)
			$Result += "$([char]0x1b)]633;D`a"
		}
		else {
			# Command finished exit code
			# OSC 633 ; D [; <ExitCode>] ST
			$Result += "$([char]0x1b)]633;D;$FakeCode`a"
		}
	}
	# Prompt started
	# OSC 633 ; A ST
	$Result += "$([char]0x1b)]633;A`a"
	# Current working directory
	# OSC 633 ; <Property>=<Value> ST
	$Result += if ($pwd.Provider.Name -eq 'FileSystem') { "$([char]0x1b)]633;P;Cwd=$(__VSCode-Escape-Value $pwd.ProviderPath)`a" }

	# Send current environment variables as JSON
	# OSC 633 ; EnvJson ; <Environment> ; <Nonce>
	if ($Global:__VSCodeState.EnvVarsToReport.Count -gt 0) {
		$envMap = @{}
        foreach ($varName in $Global:__VSCodeState.EnvVarsToReport) {
            if (Test-Path "env:$varName") {
                $envMap[$varName] = (Get-Item "env:$varName").Value
            }
        }
        $envJson = $envMap | ConvertTo-Json -Compress
        $Result += "$([char]0x1b)]633;EnvJson;$(__VSCode-Escape-Value $envJson);$($Global:__VSCodeState.Nonce)`a"
	}

	# Before running the original prompt, put $? back to what it was:
	if ($FakeCode -ne 0) {
		Write-Error "failure" -ea ignore
	}
	# Run the original prompt
	$OriginalPrompt += $Global:__VSCodeState.OriginalPrompt.Invoke()
	$Result += $OriginalPrompt

	# Prompt
	# OSC 633 ; <Property>=<Value> ST
	if ($Global:__VSCodeState.IsStable -eq "0") {
		$Result += "$([char]0x1b)]633;P;Prompt=$(__VSCode-Escape-Value $OriginalPrompt)`a"
	}

	# Write command started
	$Result += "$([char]0x1b)]633;B`a"
	$Global:__VSCodeState.LastHistoryId = $LastHistoryEntry.Id
	return $Result
}

# Report prompt type
if ($env:STARSHIP_SESSION_KEY) {
	[Console]::Write("$([char]0x1b)]633;P;PromptType=starship`a")
}
elseif ($env:POSH_SESSION_ID) {
	[Console]::Write("$([char]0x1b)]633;P;PromptType=oh-my-posh`a")
}
elseif ((Test-Path variable:global:GitPromptSettings) -and $Global:GitPromptSettings) {
	[Console]::Write("$([char]0x1b)]633;P;PromptType=posh-git`a")
}

# Only send the command executed sequence when PSReadLine is loaded, if not shell integration should
# still work thanks to the command line sequence
$Global:__VSCodeState.HasPSReadLine = $false
if (Get-Module -Name PSReadLine) {
	$Global:__VSCodeState.HasPSReadLine = $true
	[Console]::Write("$([char]0x1b)]633;P;HasRichCommandDetection=True`a")

	$Global:__VSCodeState.OriginalPSConsoleHostReadLine = $function:PSConsoleHostReadLine
	function Global:PSConsoleHostReadLine {
		$CommandLine = $Global:__VSCodeState.OriginalPSConsoleHostReadLine.Invoke()
		$Global:__VSCodeState.IsInExecution = $true

		# Command line
		# OSC 633 ; E [; <CommandLine> [; <Nonce>]] ST
		$Result = "$([char]0x1b)]633;E;"
		$Result += $(__VSCode-Escape-Value $CommandLine)
		# Only send the nonce if the OS is not Windows 10 as it seems to echo to the terminal
		# sometimes
		if ($Global:__VSCodeState.IsWindows10 -eq $false) {
			$Result += ";$($Global:__VSCodeState.Nonce)"
		}
		$Result += "`a"

		# Command executed
		# OSC 633 ; C ST
		$Result += "$([char]0x1b)]633;C`a"

		# Write command executed sequence directly to Console to avoid the new line from Write-Host
		[Console]::Write($Result)

		$CommandLine
	}

	# Set ContinuationPrompt property
	$Global:__VSCodeState.ContinuationPrompt = (Get-PSReadLineOption).ContinuationPrompt
	if ($Global:__VSCodeState.ContinuationPrompt) {
		[Console]::Write("$([char]0x1b)]633;P;ContinuationPrompt=$(__VSCode-Escape-Value $Global:__VSCodeState.ContinuationPrompt)`a")
	}
}

# Set IsWindows property
if ($PSVersionTable.PSVersion -lt "6.0") {
	# Windows PowerShell is only available on Windows
	[Console]::Write("$([char]0x1b)]633;P;IsWindows=$true`a")
}
else {
	[Console]::Write("$([char]0x1b)]633;P;IsWindows=$IsWindows`a")
}

# Set always on key handlers which map to default VS Code keybindings
function Set-MappedKeyHandler {
	param ([string[]] $Chord, [string[]]$Sequence)
	try {
		$Handler = Get-PSReadLineKeyHandler -Chord $Chord | Select-Object -First 1
	}
 catch [System.Management.Automation.ParameterBindingException] {
		# PowerShell 5.1 ships with PSReadLine 2.0.0 which does not have -Chord,
		# so we check what's bound and filter it.
		$Handler = Get-PSReadLineKeyHandler -Bound | Where-Object -FilterScript { $_.Key -eq $Chord } | Select-Object -First 1
	}
	if ($Handler) {
		Set-PSReadLineKeyHandler -Chord $Sequence -Function $Handler.Function
	}
}

function Set-MappedKeyHandlers {
	Set-MappedKeyHandler -Chord Ctrl+Spacebar -Sequence 'F12,a'
	Set-MappedKeyHandler -Chord Alt+Spacebar -Sequence 'F12,b'
	Set-MappedKeyHandler -Chord Shift+Enter -Sequence 'F12,c'
	Set-MappedKeyHandler -Chord Shift+End -Sequence 'F12,d'

	# Enable suggestions if the environment variable is set and Windows PowerShell is not being used
	# as APIs are not available to support this feature
	if ($env:VSCODE_SUGGEST -eq '1' -and $PSVersionTable.PSVersion -ge "7.0") {
		Remove-Item Env:VSCODE_SUGGEST

		# VS Code send completions request (may override Ctrl+Spacebar)
		Set-PSReadLineKeyHandler -Chord 'F12,e' -ScriptBlock {
			Send-Completions
		}
	}
}

function Send-Completions {
	$commandLine = ""
	$cursorIndex = 0
	$prefixCursorDelta = 0
	[Microsoft.PowerShell.PSConsoleReadLine]::GetBufferState([ref]$commandLine, [ref]$cursorIndex)
	$completionPrefix = $commandLine

	# Start completions sequence
	$result = "$([char]0x1b)]633;Completions"

	# Only provide completions for arguments and defer to TabExpansion2.
	# `[` is included here as namespace commands are not included in CompleteCommand(''),
	# additionally for some reason CompleteVariable('[') causes the prompt to clear and reprint
	# multiple times
	if ($completionPrefix.Contains(' ')) {

		# Adjust the completion prefix and cursor index such that tab expansion will be requested
		# immediately after the last whitespace. This allows the client to perform fuzzy filtering
		# such that requesting completions in the middle of a word should show the same completions
		# as at the start. This only happens when the last word does not include special characters:
		# - `-`: Completion change when flags are used.
		# - `/` and `\`: Completions change when navigating directories.
		# - `$`: Completions change when variables.
		$lastWhitespaceIndex = $completionPrefix.LastIndexOf(' ')
		$lastWord = $completionPrefix.Substring($lastWhitespaceIndex + 1)
		if ($lastWord -match '^-') {
			$newCursorIndex = $lastWhitespaceIndex + 2
			$completionPrefix = $completionPrefix.Substring(0, $newCursorIndex)
			$prefixCursorDelta = $cursorIndex - $newCursorIndex
			$cursorIndex = $newCursorIndex
		}
		elseif ($lastWord -notmatch '[/\\$]') {
			if ($lastWhitespaceIndex -ne -1 -and $lastWhitespaceIndex -lt $cursorIndex) {
				$newCursorIndex = $lastWhitespaceIndex + 1
				$completionPrefix = $completionPrefix.Substring(0, $newCursorIndex)
				$prefixCursorDelta = $cursorIndex - $newCursorIndex
				$cursorIndex = $newCursorIndex
			}
		}
		# If it contains `/` or `\`, get completions from the nearest `/` or `\` such that file
		# completions are consistent regardless of where it was requested
		elseif ($lastWord -match '[/\\]') {
			$lastSlashIndex = $completionPrefix.LastIndexOfAny(@('/', '\'))
			if ($lastSlashIndex -ne -1 -and $lastSlashIndex -lt $cursorIndex) {
				$newCursorIndex = $lastSlashIndex + 1
				$completionPrefix = $completionPrefix.Substring(0, $newCursorIndex)
				$prefixCursorDelta = $cursorIndex - $newCursorIndex
				$cursorIndex = $newCursorIndex
			}
		}

		# Get completions using TabExpansion2
		$completions = $null
		$completionMatches = $null
		try
		{
			$completions = TabExpansion2 -inputScript $completionPrefix -cursorColumn $cursorIndex
			$completionMatches = $completions.CompletionMatches | Where-Object { $_.ResultType -ne [System.Management.Automation.CompletionResultType]::ProviderContainer -and $_.ResultType -ne [System.Management.Automation.CompletionResultType]::ProviderItem }
		}
		catch
		{
			# TabExpansion2 may throw when there are no completions, in this case return an empty
			# list to prevent falling back to file path completions
		}
		if ($null -eq $completions -or $null -eq $completionMatches) {
			$result += ";0;$($completionPrefix.Length);$($completionPrefix.Length);[]"
		} else {
			$result += ";$($completions.ReplacementIndex);$($completions.ReplacementLength + $prefixCursorDelta);$($cursorIndex - $prefixCursorDelta);"
			$json = [System.Collections.ArrayList]@($completionMatches)
			$mappedCommands = Compress-Completions($json)
			$result += $mappedCommands | ConvertTo-Json -Compress
		}
	}

	# End completions sequence
	$result += "`a"

	Write-Host -NoNewLine $result
}

function Compress-Completions($completions) {
	$completions | ForEach-Object {
		if ($_.CustomIcon) {
			,@($_.CompletionText, $_.ResultType, $_.ToolTip, $_.CustomIcon)
		}
		elseif ($_.CompletionText -eq $_.ToolTip) {
			,@($_.CompletionText, $_.ResultType)
		} else {
			,@($_.CompletionText, $_.ResultType, $_.ToolTip)
		}
	}
}

# Register key handlers if PSReadLine is available
if (Get-Module -Name PSReadLine) {
	Set-MappedKeyHandlers
}

# SIG # Begin signature block
# MIIu8wYJKoZIhvcNAQcCoIIu5DCCLuACAQExDzANBglghkgBZQMEAgEFADB5Bgor
# BgEEAYI3AgEEoGswaTA0BgorBgEEAYI3AgEeMCYCAwEAAAQQH8w7YFlLCE63JNLG
# KX7zUQIBAAIBAAIBAAIBAAIBADAxMA0GCWCGSAFlAwQCAQUABCA07QqXI4mZ2YIC
# SSpL+4l+phC5HR9RMo+onlGtp16hZaCCFBcwggYxMIIEGaADAgECAhMzAAAAOb0d
# 20f6nVYAAAEAAAA5MA0GCSqGSIb3DQEBCwUAMIGHMQswCQYDVQQGEwJVUzETMBEG
# A1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWlj
# cm9zb2Z0IENvcnBvcmF0aW9uMTEwLwYDVQQDEyhNaWNyb3NvZnQgTWFya2V0cGxh
# Y2UgUHJvZHVjdGlvbiBDQSAyMDExMB4XDTI1MDYxOTE4NTQxNFoXDTI2MDYxNzE4
# NTQxNFowdDELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNV
# BAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEeMBwG
# A1UEAxMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMIIBIjANBgkqhkiG9w0BAQEFAAOC
# AQ8AMIIBCgKCAQEAtdIdYPZGr5OPIrWkmxTpozsk8RnWxnTYkMnchCH1uxSHAAEG
# RgzhGbD7s32XpJ+XX2hgepvkkQuwVCAWJCw568PSrXoChWYBJVDonwZSphS48Diz
# NuoqhZmp61pqt+p+94Xbli9gtBqk1RBxuEaX6SHbG6JfbIKeOsR6iiMvXsuLoDP4
# G6xf1iBhodE43l7I6mcHnSnmtnrUZCDgrOYN0C4nnf8tExsfcNQ69oX2CyXd3k/2
# f3YFGatRzFjMWY7DKZ5OoUW/igxm7TgspmXgue/JpY1yuO2eOG/Us1LjeNDCa6x9
# UwRMQf3J8X29TQlesnOapdGzP3PRGAGo3/wqlwIDAQABo4IBpjCCAaIwEwYDVR0l
# BAwwCgYIKwYBBQUHAwMwHQYDVR0OBBYEFBxpSPRkCMknX2x4/vfIokCCS6/5MFQG
# A1UdEQRNMEukSTBHMS0wKwYDVQQLEyRNaWNyb3NvZnQgSXJlbGFuZCBPcGVyYXRp
# b25zIExpbWl0ZWQxFjAUBgNVBAUTDTIyOTk3OSs1MDUzMDYwHwYDVR0jBBgwFoAU
# nqf5oCNwnxHFaeOhjQr68bD01YAwbAYDVR0fBGUwYzBhoF+gXYZbaHR0cDovL3d3
# dy5taWNyb3NvZnQuY29tL3BraW9wcy9jcmwvTWljcm9zb2Z0JTIwTWFya2V0cGxh
# Y2UlMjBQcm9kdWN0aW9uJTIwQ0ElMjAyMDExKDEpLmNybDB5BggrBgEFBQcBAQRt
# MGswaQYIKwYBBQUHMAKGXWh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMv
# Y2VydHMvTWljcm9zb2Z0JTIwTWFya2V0cGxhY2UlMjBQcm9kdWN0aW9uJTIwQ0El
# MjAyMDExKDEpLmNydDAMBgNVHRMBAf8EAjAAMA0GCSqGSIb3DQEBCwUAA4ICAQBZ
# QQS8MMpdKn3gQxAKmAS6isRYEP2Tz9k/l/zIRoSthAYXhpe5DtlKxvuQQcpEzBuw
# G5M89QaiCZaFVfosu9fXh2R4FK4RCJDwm/zV0PWBY7ZBfjgX2+RljYffHJ5GY7YX
# VV4WIh9hMw220sQ0xg3+BCM9qHjUKx1fDUZINcJLTU/dDJQ1cLKvSYISLA9VlC0F
# dArywD+SCpvL0TUQmRY2kw4VzRx3fP0aPLhbDVcUQc9P9Wuwx/dp+2faji+Ug2aD
# y9CgDHqNGQAP9MhZpQYnr78q/s4BHDxdGmTjfvvgBvIrmIM4nq0F921G5CSFatbi
# srUEN2M+Jk3jMfWciiVTvv2y/wE0MXt+R+hJhyhqlObMJSIr0tFles7fD2sBs+5m
# ccBsMCwt7S+gqtlBr5J/9yn07XSkKJlZSAiDx0MvqWVyBBGvu8QDv4saUjNOG7nH
# JSfpaP66cF3shogzmGad2T+il7p0kmvvTgEX2RQ64x252Hur2DlEmYE1GE5b8bLb
# +7rXwFbsdzR+Gytz/MmKQK5c1LaHJT21guU+AbeRKAPbgs6UajiLBPiGamqhG+Y6
# u8VvH71qKGNBrO+3+Fa3IeGh2R/JdedigfKUQX7NyA8wPlLx3HM4+kQJqZIF2dL1
# N0v4QYELCuZ6a8sxFZFslkLb0zQpVewg91s5rblo6DCCBtcwggS/oAMCAQICCmES
# RKIAAAAAAAIwDQYJKoZIhvcNAQELBQAwgYgxCzAJBgNVBAYTAlVTMRMwEQYDVQQI
# EwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3Nv
# ZnQgQ29ycG9yYXRpb24xMjAwBgNVBAMTKU1pY3Jvc29mdCBSb290IENlcnRpZmlj
# YXRlIEF1dGhvcml0eSAyMDExMB4XDTExMDMyODIxMDkzOVoXDTMxMDMyODIxMTkz
# OVowfTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcT
# B1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEnMCUGA1UE
# AxMeTWljcm9zb2Z0IE1hcmtldFBsYWNlIFBDQSAyMDExMIICIjANBgkqhkiG9w0B
# AQEFAAOCAg8AMIICCgKCAgEAubUaSwGYVsE3MAnPfvmozUhAB3qxBABgJRW1vDp4
# +tVinXxD32f7k1K89JQ6zDOgS/iDgULC+yFK1K/1Qjac/0M7P6c8v5LSjnWGlERL
# a/qY32j46S7SLQcit3g2jgoTTO03eUG+9yHZUTGV/FJdRYB8uXhrznJBa+Y+yGwi
# QKF+m6XFeBH/KORoKFx+dmMoy9EWJ/m/o9IiUj2kzm9C691+vZ/I2w0Bj93W9SPP
# kV2PCNHlzgfIAoeajWpHmi38Wi3xZHonkzAVBHxPsCBppOoNsWvmAfUM7eBthkSP
# vFruekyDCPNEYhfGqgqtqLkoBebXLZCOVybF7wTQaLvse60//3P003icRcCoQYgY
# 4NAqrF7j80o5U7DkeXxcB0xvengsaKgiAaV1DKkRbpe98wCqr1AASvm5rAJUYMU+
# mXmOieV2EelY2jGrenWe9FQpNXYV1NoWBh0WKoFxttoWYAnF705bIWtSZsz08ZfK
# 6WLX4GXNLcPBlgCzfTm1sdKYASWdBbH2haaNhPapFhQQBJHKwnVW2iXErImhuPi4
# 5W3MVTZ5D9ASshZx69cLYY6xAdIa+89Kf/uRrsGOVZfahDuDw+NI183iAyzC8z/Q
# Rt2P32LYxP0xrCdqVh+DJo2i4NoE8Uk1usCdbVRuBMBQl/AwpOTq7IMvHGElf65C
# qzUCAwEAAaOCAUswggFHMBAGCSsGAQQBgjcVAQQDAgEAMB0GA1UdDgQWBBQPU8s/
# FmEl/mCJHdO5fOiQrbOU0TAZBgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMAQTALBgNV
# HQ8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAfBgNVHSMEGDAWgBRyLToCMZBDuRQF
# TuHqp8cx0SOJNDBaBgNVHR8EUzBRME+gTaBLhklodHRwOi8vY3JsLm1pY3Jvc29m
# dC5jb20vcGtpL2NybC9wcm9kdWN0cy9NaWNSb29DZXJBdXQyMDExXzIwMTFfMDNf
# MjIuY3JsMF4GCCsGAQUFBwEBBFIwUDBOBggrBgEFBQcwAoZCaHR0cDovL3d3dy5t
# aWNyb3NvZnQuY29tL3BraS9jZXJ0cy9NaWNSb29DZXJBdXQyMDExXzIwMTFfMDNf
# MjIuY3J0MA0GCSqGSIb3DQEBCwUAA4ICAQCjuZmM8ZVNDgp9wHsL4RY8KJ8nLinv
# xFTphNGCrxaLknkYG5pmMhVlX+UB/tSiW8W13W60nggz9u5xwMx7v/1t/Tgm6g2b
# rVyOKI5A7u6/2SIJwkJKFw953K0YIKVT28w9zl8dSJnmRnyR0G86ncWbF6CLQ6A6
# lBQ9o2mTGVqDr4m35WKAnc6YxUUM1y74mbzFFZr63VHsCcOp3pXWnUqAY1rb6Q6N
# X1b3clncKqLFm0EjKHcQ56grTbwuuB7pMdh/IFCJR01MQzQbDtpEisbOeZUi43YV
# AAHKqI1EO9bRwg3frCjwAbml9MmI4utMW94gWFgvrMxIX+n42RBDIjf3Ot3jkT6g
# t3XeTTmO9bptgblZimhERdkFRUFpVtkocJeLoGuuzP93uH/Yp032wzRH+XmMgujf
# Zv+vnfllJqxdowoQLx55FxLLeTeYfwi/xMSjZO2gNven3U/3KeSCd1kUOFS3AOrw
# Z0UNOXJeW5JQC6Vfd1BavFZ6FAta1fMLu3WFvNB+FqeHUaU3ya7rmtxJnzk29DeS
# qXgGNmVSywBS4NajI5jJIKAA6UhNJlsg8CHYwUOKf5ej8OoQCkbadUxXygAfxCfW
# 2YBbujtI+PoyejRFxWUjYFWO5LeTI62UMyqfOEiqugoYjNxmQZla2s4YHVuqIC34
# R85FQlg9pKQBsDCCBwMwggTroAMCAQICEzMAAABVyAZrOCOXKQkAAAAAAFUwDQYJ
# KoZIhvcNAQELBQAwfTELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24x
# EDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlv
# bjEnMCUGA1UEAxMeTWljcm9zb2Z0IE1hcmtldFBsYWNlIFBDQSAyMDExMB4XDTIx
# MDkwOTIyNDIzMFoXDTMwMDkwOTIyNTIzMFowgYcxCzAJBgNVBAYTAlVTMRMwEQYD
# VQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNy
# b3NvZnQgQ29ycG9yYXRpb24xMTAvBgNVBAMTKE1pY3Jvc29mdCBNYXJrZXRwbGFj
# ZSBQcm9kdWN0aW9uIENBIDIwMTEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIK
# AoICAQDHfQ3P+L0El1S6JNYAz70y3e1i7EZAYcCDVXde/nQdpOKtVr6H4QkBkROv
# 7HBxY0U8lR9C3bUUZKn6CCcN3v3bQuYKu1Ff2G4nIIr8a1cB4iOU8i4YSN7bRr+5
# LvD5hyCfJHqXrJe5LRRGjws5aRAxYuGhQ3ypWPEZYfrIXmmYK+e+udApgxahHUPB
# qcbI2PT1PpkKDgqR7hyzW0CfWzRUwh+YoZpsVvDaEkxcHQe/yGJB5BluYyRm5K9z
# +YQqBvYJkNUisTE/9OImnaZqoujkEuhM5bBV/dNjw7YN37OcBuH0NvlQomLQo+V7
# PA519HVVE1kRQ8pFad6i4YdRWpj/+1yFskRZ5m7y+dEdGyXAiFeIgaM6O1CFrA1L
# bMAvyaZpQwBkrT/etC0hw4BPmW70zSmSubMoHpx/UUTNo3fMUVqx6r2H1xsc4aXT
# pPN5IxjkGIQhPN6h3q5JC+JOPnsfDRg3Ive2Q22jj3tkNiOXrYpmkILk7v+4XUxD
# Erdc/WLZ3sbF27hug7HSVbTCNA46scIqE7ZkgH3M7+8aP3iUBDNcYUWjO1u+P1Q6
# UUzFdShSbGbKf+Z3xpqlwdxQq9kuUahACRQLMFjRUfmAqGXUdMXECRaFPTxl6SB/
# 7IAcuK855beqNPcexVEpkSZxZJbnqjKWbyTk/GA1abW8zgfH2QIDAQABo4IBbzCC
# AWswEgYJKwYBBAGCNxUBBAUCAwEAATAjBgkrBgEEAYI3FQIEFgQUeBlfau2VIfkw
# k2K+EoAD6hZ05ccwHQYDVR0OBBYEFJ6n+aAjcJ8RxWnjoY0K+vGw9NWAMBkGCSsG
# AQQBgjcUAgQMHgoAUwB1AGIAQwBBMAsGA1UdDwQEAwIBhjASBgNVHRMBAf8ECDAG
# AQH/AgEAMB8GA1UdIwQYMBaAFA9Tyz8WYSX+YIkd07l86JCts5TRMFcGA1UdHwRQ
# ME4wTKBKoEiGRmh0dHA6Ly9jcmwubWljcm9zb2Z0LmNvbS9wa2kvY3JsL3Byb2R1
# Y3RzL01pY01hclBDQTIwMTFfMjAxMS0wMy0yOC5jcmwwWwYIKwYBBQUHAQEETzBN
# MEsGCCsGAQUFBzAChj9odHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vcGtpL2NlcnRz
# L01pY01hclBDQTIwMTFfMjAxMS0wMy0yOC5jcnQwDQYJKoZIhvcNAQELBQADggIB
# ACY4RaglNFzKOO+3zgazCsgCvXca79D573wDc0DAj6KzBX9m4rHhAZqzBkfSWvan
# LFilDibWmbGUGbkuH0y29NEoLVHfY64PXmXcBWEWd1xK4QxyKx2VVDq9P9494Z/v
# Xy9OsifTP8Gt2UkhftAQMcvKgGiAHtyRHda8r7oU4cc4ITZnMsgXv6GnMDVuIk+C
# q0Eh93rgzKF2rJ1sJcraH/kgSkgawBYYdJlXXHTkOrfEPKU82BDT5h8SGsXVt5L1
# mwRzjVQRLs1FNPkA+Kqyz0L+UEXJZWldNtHC79XtYh/ysRov4Yu/wLF+c8Pm15IC
# n8EYJUL4ZKmk9ZM7ZcaUV/2XvBpufWE2rcMnS/dPHWIojQ1FTToqM+Ag2jZZ33fl
# 8rJwnnIF/Ku4OZEN24wQLYsOMHh6WKADxkXJhiYUwBe2vCMHDVLpbCY7CbPpQdtB
# YHEkto0MFADdyX50sNVgTKboPyCxPW6GLiR5R+qqzNRzpYru2pTsM6EodSTgcMbe
# aDZI7ssnv+NYMyWstE1IXQCUywLQohNDo6H7/HNwC8HtdsGd5j0j+WOIEO5PyCbj
# n5viNWWCUu7Ko6Qx68NuxHf++swe9YQhufh0hzJnixidTRPkBUgYQ6xubG6I5g/2
# OO1BByOu9/jt5vMTTvctq2YWOhUjoOZPe53eYSzjvNydMYIaMjCCGi4CAQEwgZ8w
# gYcxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdS
# ZWRtb25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xMTAvBgNVBAMT
# KE1pY3Jvc29mdCBNYXJrZXRwbGFjZSBQcm9kdWN0aW9uIENBIDIwMTECEzMAAAA5
# vR3bR/qdVgAAAQAAADkwDQYJYIZIAWUDBAIBBQCggbAwGQYJKoZIhvcNAQkDMQwG
# CisGAQQBgjcCAQQwHAYKKwYBBAGCNwIBCzEOMAwGCisGAQQBgjcCARUwLwYJKoZI
# hvcNAQkEMSIEILn0/rsIqydMEZiSuFGCnfXpIMefLSEUWOZbUpR6zrWNMEQGCisG
# AQQBgjcCAQwxNjA0oBCADgBWAFMAIABDAG8AZABloSCAHmh0dHBzOi8vY29kZS52
# aXN1YWxzdHVkaW8uY29tLzANBgkqhkiG9w0BAQEFAASCAQAbmlqSOJV9ZkdGYb4e
# 0cE5Ylr2dMBP19vyWot8OS71VBEkBLqI2w6ZXDVtqv04u1DyoiOalIgMgo317XvB
# PGjXJ7DqJWsS/BBA25T+o5CPa3q9vpyM/5MbBrhOfa19RlDV6iTkMiC6Ugff8zt3
# 7OmpLe5PhAK8i0wR2msIYYf0Rpi/8cXKdeQDGTmY/OI6NopcRmBgJwyPFawJ9ZTR
# 0uymOJcdeAj2dsZgBotVZATfucjQHW6ceszj3tCxN5TrV9P2RImSb89xXT+kUpWG
# wf5FCvK4KIlpK0gRxewL7XLTCbRmnjQZj9tX2cpBWvAQOV3Fhzm7dWsR8qXW5amQ
# o7X6oYIXsDCCF6wGCisGAQQBgjcDAwExghecMIIXmAYJKoZIhvcNAQcCoIIXiTCC
# F4UCAQMxDzANBglghkgBZQMEAgEFADCCAVoGCyqGSIb3DQEJEAEEoIIBSQSCAUUw
# ggFBAgEBBgorBgEEAYRZCgMBMDEwDQYJYIZIAWUDBAIBBQAEIBbc6sgS937CRmsZ
# oeXWNvbIay2J8wGGCUom7X7OI7ClAgZoelnwGjIYEzIwMjUwODA2MjE1OTMxLjI2
# NFowBIACAfSggdmkgdYwgdMxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpXYXNoaW5n
# dG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9y
# YXRpb24xLTArBgNVBAsTJE1pY3Jvc29mdCBJcmVsYW5kIE9wZXJhdGlvbnMgTGlt
# aXRlZDEnMCUGA1UECxMeblNoaWVsZCBUU1MgRVNOOjJEMUEtMDVFMC1EOTQ3MSUw
# IwYDVQQDExxNaWNyb3NvZnQgVGltZS1TdGFtcCBTZXJ2aWNloIIR/jCCBygwggUQ
# oAMCAQICEzMAAAH9c/loWs0MYe0AAQAAAf0wDQYJKoZIhvcNAQELBQAwfDELMAkG
# A1UEBhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQx
# HjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEmMCQGA1UEAxMdTWljcm9z
# b2Z0IFRpbWUtU3RhbXAgUENBIDIwMTAwHhcNMjQwNzI1MTgzMTE2WhcNMjUxMDIy
# MTgzMTE2WjCB0zELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAO
# BgNVBAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEt
# MCsGA1UECxMkTWljcm9zb2Z0IElyZWxhbmQgT3BlcmF0aW9ucyBMaW1pdGVkMScw
# JQYDVQQLEx5uU2hpZWxkIFRTUyBFU046MkQxQS0wNUUwLUQ5NDcxJTAjBgNVBAMT
# HE1pY3Jvc29mdCBUaW1lLVN0YW1wIFNlcnZpY2UwggIiMA0GCSqGSIb3DQEBAQUA
# A4ICDwAwggIKAoICAQChZaz4P467gmNidEdF527QxMVjM0kRU+cgvNzTZHepue6O
# +FmCSGn6n+XKZgvORDIbbOnFhx5OMgXseJBZu3oVbcBGQGu2ElTPTlmcqlwXfWWl
# QRvyBReIPbEimjxgz5IPRL6FM/VMID/B7fzJncES2Zm1xWdotGn8C+yqD7kojQrD
# pMMmkrBMuXRVbT/bewqKR5YNKcdB5Oms7TMib9u1qBJibdX/zNeV/HLuz8RUV1KC
# UcaxSrwRm6lQ7xdsfPPu1RHKIPeQ7E2fDmjHV5lf9z9eZbgfpvjI2ZkXTBNm7Dfv
# IDU8ko7JJKtetYSH4fr75Zvr7WW0wI+gwkdS08/cKfQI1w2+s/Im0NpyqOchOsvO
# uwd04uqOwfbb1mS+d2TQirEENmAyhj4R/t98VE/ak+SsXUX0hwGRjPyEv5CNf67j
# LhSqrhS1PtVGeyq9H/H/5AsTSlxISH9cTXDV9ynomarxGccReKTJwws39r8pjGlI
# /cV8Vstm5/6oivIUvSAQPK1qkafU42NWSIqlU/a6pUhiPhWIKPLmktRx4x6qIqBi
# qGmZQcITZaywsuF1AEd2mXbz6T5ljqbh08WcSgZwke4xwhmfDhw7CLGiNE6v42rv
# VwmPtDgvRfA++5MdC3SgftEoxCCazLsJUPu/nl06F0dd1izI7r10B0r6daXJhwID
# AQABo4IBSTCCAUUwHQYDVR0OBBYEFOkMxcDhlbz7Ivb7e8DpGZTugQqkMB8GA1Ud
# IwQYMBaAFJ+nFV0AXmJdg/Tl0mWnG1M1GelyMF8GA1UdHwRYMFYwVKBSoFCGTmh0
# dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY3JsL01pY3Jvc29mdCUyMFRp
# bWUtU3RhbXAlMjBQQ0ElMjAyMDEwKDEpLmNybDBsBggrBgEFBQcBAQRgMF4wXAYI
# KwYBBQUHMAKGUGh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY2VydHMv
# TWljcm9zb2Z0JTIwVGltZS1TdGFtcCUyMFBDQSUyMDIwMTAoMSkuY3J0MAwGA1Ud
# EwEB/wQCMAAwFgYDVR0lAQH/BAwwCgYIKwYBBQUHAwgwDgYDVR0PAQH/BAQDAgeA
# MA0GCSqGSIb3DQEBCwUAA4ICAQBj2Fhf5PkCYKtgZof3pN1HlPnb8804bvJJh6im
# /h+WcNZAuEGWtq8CD6mOU2/ldJdmsoa/x7izl0nlZ2F8L3LAVCrhOZedR689e2W5
# tmT7TYFcrr/beEzRNIqzYqWFiKrNtF7xBsx8pcQO28ygdJlPuv7AjYiCNhDCRr7c
# /1VeARHC7jr9zPPwhH9mr687nnbcmV3qyxW7Oz27AismF9xgGPnSZdZEFwyHNqMu
# NYOByKHQO7KQ9wGmhMuU4vwuleiiqev5AtgTgGlR6ncnJIxh8/PaF84veDTZYR+w
# 7GnwA1tx2KozfV2be9KF4SSaMcDbO4z5OCfiPmf4CfLsg4NhCQis1WEt0wvT167V
# 0g+GnbiUW2dZNg1oVM58yoVrcBvwoMqJyanQC2FE1lWDQE8Avnz4HRRygEYrNL2O
# xzA5O7UmY2WKw4qRVRWRInkWj9y18NI90JNVohdcXuXjSTVwz9fY7Ql0BL3tPvyV
# iO3D8/Ju7NfmyHEGH9GpM+8LICEjEFUp83+F+zgIigVqpYnSv/xIHUIazLIhw98S
# Ayjxx6rXDlmjQl+fIWLoa6j7Pcs8WX97FBpG5sSuwBRN/IFjn/mWLK+MCDINicQH
# y8c7tzsWDa0Z3mEaBiz4A6hbHbj5dzLGlSQBqMOGTL0OX7wllOO2zoFxP2xhOY6h
# 2T9KAjCCB3EwggVZoAMCAQICEzMAAAAVxedrngKbSZkAAAAAABUwDQYJKoZIhvcN
# AQELBQAwgYgxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYD
# VQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xMjAw
# BgNVBAMTKU1pY3Jvc29mdCBSb290IENlcnRpZmljYXRlIEF1dGhvcml0eSAyMDEw
# MB4XDTIxMDkzMDE4MjIyNVoXDTMwMDkzMDE4MzIyNVowfDELMAkGA1UEBhMCVVMx
# EzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNVBAoT
# FU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEmMCQGA1UEAxMdTWljcm9zb2Z0IFRpbWUt
# U3RhbXAgUENBIDIwMTAwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQDk
# 4aZM57RyIQt5osvXJHm9DtWC0/3unAcH0qlsTnXIyjVX9gF/bErg4r25PhdgM/9c
# T8dm95VTcVrifkpa/rg2Z4VGIwy1jRPPdzLAEBjoYH1qUoNEt6aORmsHFPPFdvWG
# UNzBRMhxXFExN6AKOG6N7dcP2CZTfDlhAnrEqv1yaa8dq6z2Nr41JmTamDu6Gnsz
# rYBbfowQHJ1S/rboYiXcag/PXfT+jlPP1uyFVk3v3byNpOORj7I5LFGc6XBpDco2
# LXCOMcg1KL3jtIckw+DJj361VI/c+gVVmG1oO5pGve2krnopN6zL64NF50ZuyjLV
# wIYwXE8s4mKyzbnijYjklqwBSru+cakXW2dg3viSkR4dPf0gz3N9QZpGdc3EXzTd
# EonW/aUgfX782Z5F37ZyL9t9X4C626p+Nuw2TPYrbqgSUei/BQOj0XOmTTd0lBw0
# gg/wEPK3Rxjtp+iZfD9M269ewvPV2HM9Q07BMzlMjgK8QmguEOqEUUbi0b1qGFph
# AXPKZ6Je1yh2AuIzGHLXpyDwwvoSCtdjbwzJNmSLW6CmgyFdXzB0kZSU2LlQ+QuJ
# YfM2BjUYhEfb3BvR/bLUHMVr9lxSUV0S2yW6r1AFemzFER1y7435UsSFF5PAPBXb
# GjfHCBUYP3irRbb1Hode2o+eFnJpxq57t7c+auIurQIDAQABo4IB3TCCAdkwEgYJ
# KwYBBAGCNxUBBAUCAwEAATAjBgkrBgEEAYI3FQIEFgQUKqdS/mTEmr6CkTxGNSnP
# EP8vBO4wHQYDVR0OBBYEFJ+nFV0AXmJdg/Tl0mWnG1M1GelyMFwGA1UdIARVMFMw
# UQYMKwYBBAGCN0yDfQEBMEEwPwYIKwYBBQUHAgEWM2h0dHA6Ly93d3cubWljcm9z
# b2Z0LmNvbS9wa2lvcHMvRG9jcy9SZXBvc2l0b3J5Lmh0bTATBgNVHSUEDDAKBggr
# BgEFBQcDCDAZBgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMAQTALBgNVHQ8EBAMCAYYw
# DwYDVR0TAQH/BAUwAwEB/zAfBgNVHSMEGDAWgBTV9lbLj+iiXGJo0T2UkFvXzpoY
# xDBWBgNVHR8ETzBNMEugSaBHhkVodHRwOi8vY3JsLm1pY3Jvc29mdC5jb20vcGtp
# L2NybC9wcm9kdWN0cy9NaWNSb29DZXJBdXRfMjAxMC0wNi0yMy5jcmwwWgYIKwYB
# BQUHAQEETjBMMEoGCCsGAQUFBzAChj5odHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20v
# cGtpL2NlcnRzL01pY1Jvb0NlckF1dF8yMDEwLTA2LTIzLmNydDANBgkqhkiG9w0B
# AQsFAAOCAgEAnVV9/Cqt4SwfZwExJFvhnnJL/Klv6lwUtj5OR2R4sQaTlz0xM7U5
# 18JxNj/aZGx80HU5bbsPMeTCj/ts0aGUGCLu6WZnOlNN3Zi6th542DYunKmCVgAD
# sAW+iehp4LoJ7nvfam++Kctu2D9IdQHZGN5tggz1bSNU5HhTdSRXud2f8449xvNo
# 32X2pFaq95W2KFUn0CS9QKC/GbYSEhFdPSfgQJY4rPf5KYnDvBewVIVCs/wMnosZ
# iefwC2qBwoEZQhlSdYo2wh3DYXMuLGt7bj8sCXgU6ZGyqVvfSaN0DLzskYDSPeZK
# PmY7T7uG+jIa2Zb0j/aRAfbOxnT99kxybxCrdTDFNLB62FD+CljdQDzHVG2dY3RI
# LLFORy3BFARxv2T5JL5zbcqOCb2zAVdJVGTZc9d/HltEAY5aGZFrDZ+kKNxnGSgk
# ujhLmm77IVRrakURR6nxt67I6IleT53S0Ex2tVdUCbFpAUR+fKFhbHP+CrvsQWY9
# af3LwUFJfn6Tvsv4O+S3Fb+0zj6lMVGEvL8CwYKiexcdFYmNcP7ntdAoGokLjzba
# ukz5m/8K6TT4JDVnK+ANuOaMmdbhIurwJ0I9JZTmdHRbatGePu1+oDEzfbzL6Xu/
# OHBE0ZDxyKs6ijoIYn/ZcGNTTY3ugm2lBRDBcQZqELQdVTNYs6FwZvKhggNZMIIC
# QQIBATCCAQGhgdmkgdYwgdMxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpXYXNoaW5n
# dG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9y
# YXRpb24xLTArBgNVBAsTJE1pY3Jvc29mdCBJcmVsYW5kIE9wZXJhdGlvbnMgTGlt
# aXRlZDEnMCUGA1UECxMeblNoaWVsZCBUU1MgRVNOOjJEMUEtMDVFMC1EOTQ3MSUw
# IwYDVQQDExxNaWNyb3NvZnQgVGltZS1TdGFtcCBTZXJ2aWNloiMKAQEwBwYFKw4D
# AhoDFQCiPRa1VVBQ1Iqiq2uOKdECwFR2g6CBgzCBgKR+MHwxCzAJBgNVBAYTAlVT
# MRMwEQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQK
# ExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xJjAkBgNVBAMTHU1pY3Jvc29mdCBUaW1l
# LVN0YW1wIFBDQSAyMDEwMA0GCSqGSIb3DQEBCwUAAgUA7D3jeDAiGA8yMDI1MDgw
# NjE0MjE0NFoYDzIwMjUwODA3MTQyMTQ0WjB3MD0GCisGAQQBhFkKBAExLzAtMAoC
# BQDsPeN4AgEAMAoCAQACAhsbAgH/MAcCAQACAhLEMAoCBQDsPzT4AgEAMDYGCisG
# AQQBhFkKBAIxKDAmMAwGCisGAQQBhFkKAwKgCjAIAgEAAgMHoSChCjAIAgEAAgMB
# hqAwDQYJKoZIhvcNAQELBQADggEBAD6lQ0GyhsDmgEhXxEug/B64NVJRQvwe7oCv
# WemHY3Dxse+6hDQeS/jV9kNhS1iXBhrAW2YEGvZZBoKkMFC2ECRu6XoYMn3XKLFg
# ntoht4Y7MboYYteyvFuaUr1U+IFvoUxC0M9PwuG79YvMDowt8T+NfG4pNdRfTtX+
# zo/U59Vwiw95zoaZT8C6OTbqg5/oOlmc/Pl80yx21DLlXP2p8I833OmHnavrNJgR
# dS65d2jGhAOTN5oTJSRiaVeqHPR0UPCqvl+enxGRJrUrwZWaYb+IgQBxeJcdGKaW
# l15qfTbGrKQIVdSOV+kqWolfUfI0WE/k5CSMKtAcDCdgFJBczOQxggQNMIIECQIB
# ATCBkzB8MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4GA1UE
# BxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSYwJAYD
# VQQDEx1NaWNyb3NvZnQgVGltZS1TdGFtcCBQQ0EgMjAxMAITMwAAAf1z+WhazQxh
# 7QABAAAB/TANBglghkgBZQMEAgEFAKCCAUowGgYJKoZIhvcNAQkDMQ0GCyqGSIb3
# DQEJEAEEMC8GCSqGSIb3DQEJBDEiBCBCtuG0VmdcM2LYZMndUIbgCQELYUno1nel
# NEy/jE+f6TCB+gYLKoZIhvcNAQkQAi8xgeowgecwgeQwgb0EIIAoSA3JSjC8h/H9
# 4N9hK6keR4XWnoYXCMoGzyVEHg1HMIGYMIGApH4wfDELMAkGA1UEBhMCVVMxEzAR
# BgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1p
# Y3Jvc29mdCBDb3Jwb3JhdGlvbjEmMCQGA1UEAxMdTWljcm9zb2Z0IFRpbWUtU3Rh
# bXAgUENBIDIwMTACEzMAAAH9c/loWs0MYe0AAQAAAf0wIgQgG24wXAgrzYo60vA4
# Nv5usXeo4+vGEMKAG8Ch1Bbd3SUwDQYJKoZIhvcNAQELBQAEggIATZjAyCikJoAt
# VyKwmoS7V1CGuTjsxhMdjsmyVCZareodjwNLJ38jaC/V5kFazlXJPcfqq9EDNGiJ
# Dy5l108dKTB35dSHeZQIBp0WGdk07/OSl3y7V5vj+yC09wWn6pgju9HklAqFYRNH
# eNghzk8uz3VFqDqs1T9k/1oM6PtvYKsp4FsLOBV9lwfqp6vc2r/3wD/b1TTK9gUM
# 2oAdPGhntgQP5UclgVP9kNrGi/C/aSVCgJg/KsK0Bdv4XoJknsxioQXmcj2huJwl
# co2b65tAhcuzDWZbRe39Z3huVgBkz/K1TSv/VoDEQSh0PjHI0mKLLFZNP88E7jTd
# T5WqlAU2yyiFjCYc7xvVc5kbOgqvPo47aHLuls+UC4wPZ6yTV8IZDhyLBtvNs2oR
# UpPfccySKvfp6LbMZdgwD0TiRYB3Nf88qOvU+Je/m2rgIYo8qE7cCGLRqNLZubka
# YLewpX+FYKSIgS7g4LxGVGRg1Qud9gaWjbB54h66gVDmsZMGZP20QBcmoePDkuWe
# eDUfMddfpp4HuHy+T7F2sDzZh8Xf4hRz4+fSeWFfym0yx65ERy3s1oTy3evtUXy7
# ucDfdP0qNeX+92ek3bU34GOGOPdgO6fcNw3CKyjllOe+0APgAV7oUu3yiusHHP2O
# QQZr00O3C+k5Tjml8EyGgfU6cZdSowM=
# SIG # End signature block
