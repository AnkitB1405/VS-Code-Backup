// Centralized content model for easy CV updates without touching UI components.
export const profile = {
  name: 'Ankit Bembalgi',
  role: 'Cybersecurity and AI Enthusiast',
  location: 'India',
  tagline:
    'Exploring systems, security, and intelligent technologies through practical, hands-on experimentation.',
  aboutParagraphs: [
    'I am a cybersecurity and AI enthusiast currently pursuing a B.Tech in Computer Science with a specialization in Artificial Intelligence and Machine Learning at PES University. I actively explore systems, security, and emerging technologies through hands-on experimentation.',
    'I maintain an active homelab environment where I experiment with networking, containerization, and self-hosted tools. I enjoy solving Capture The Flag (CTF) cybersecurity challenges and exploring practical aspects of system security.',
    'I am also a member of LAYER8, the official cybersecurity club of PES University, where I collaborate with peers on security-related activities and learning initiatives.'
  ],
  expertise: [
    'Cybersecurity learning through CTF and practical labs',
    'AI and emerging technology exploration',
    'Linux-based development and terminal-driven workflows',
    'Systems experimentation with containers and self-hosting'
  ],
  email: 'ankitbembalgi@gmail.com',
  github: 'https://github.com/AnkitB1405',
  linkedin: 'https://www.linkedin.com/in/ankit-bembalgi-b65b55297/',
  resumeUrl: '/resume.pdf',
  heroHighlights: [
    'Offensive Security & CTF Challenges',
    'Homelab Infrastructure Engineering',
    'Linux Systems & Automation'
  ]
};

export const education = {
  university: 'PES University EC Campus',
  degree:
    'B.Tech in Computer Science and Engineering (Artificial Intelligence and Machine Learning)',
  duration: '2024 - 2028'
};

export const skills = {
  programmingLanguages: ['Python', 'C', 'Bash / Shell', 'Powershell'],
  webTechnologies: ['HTML5', 'JavaScript'],
  toolsAndTechnologies: ['Docker', 'Git', 'Linux', 'VS Code'],
  otherTechnicalInterests: [
    'Homelab experimentation',
    'Linux environments and terminal workflows',
    'System configuration and automation'
  ]
};

export const projects = [
  {
    title: 'HomeLab',
    description:
      'Personal homelab environment for hands-on experimentation with self-hosting, virtualization, containerized services, and networking workflows. It serves as a controlled sandbox to test tools, practice system administration, and automate deployments while keeping services stable through container isolation.',
    keyFeatures: [
      'Proxmox-based virtualization for efficient resource management.',
      'Containerized services for testing infrastructure and self-hosted tools.',
      'Automation workflows using n8n in dedicated containers.',
      'Environment for locally hosted AI models and developer tooling.'
    ],
    techStack: ['Linux', 'Docker', 'Networking'],
    github: '',
    demo: ''
  },
  {
    title: 'LifeHub',
    description:
      'LifeHub is a student-focused productivity platform that combines planning, budgeting, and progress tracking in one workspace. It is designed to help manage tasks, goals, and spending with a clean, maintainable architecture that supports feature growth and long-term usability.',
    keyFeatures: [
      'Unified dashboard for tasks, planning, and progress visibility.',
      'Budgeting and expense tracking for better spending awareness.',
      'Goal and milestone tracking with clear progress indicators.',
      'Modular architecture designed for future feature expansion.'
    ],
    techStack: ['JavaScript', 'HTML5'],
    github: '',
    demo: ''
  },
  {
    title: 'Active Cyber Deception',
    status: 'in-progress',
    statusLabel: 'In Progress',
    description:
      'Honeypot-based cybersecurity system designed to capture and analyze attacker behavior and surface vulnerabilities and potential attack paths through a Wazuh dashboard.',
    keyFeatures: [
      'Deploys honeypot services to attract and log malicious activity.',
      'Collects and analyzes attack telemetry from adversary interactions.',
      'Integrates with Wazuh SIEM for visualization, alerting, and analysis.',
      'Helps identify vulnerabilities and potential exploitation paths.'
    ],
    techStack: ['Cybersecurity', 'Honeypot', 'Wazuh SIEM', 'Telemetry Analysis'],
    github: '',
    demo: ''
  }
];

export const experiences = [
  {
    period: '2024 - Present',
    title: 'Member',
    organization: 'LAYER8, PES University',
    details:
      'Participating in cybersecurity-focused activities, collaborative learning sessions, and practical security exploration with peers.'
  },
  {
    period: '2024 - Present',
    title: 'CTF Learner',
    organization: 'Independent Practice',
    details:
      'Regularly solving Capture The Flag challenges to strengthen practical skills in system security, analysis, and problem solving.'
  },
  {
    period: '2024 - Present',
    title: 'Homelab Practitioner',
    organization: 'Personal Lab Environment',
    details:
      'Building and maintaining self-hosted environments for networking experiments, containerized services, and workflow automation.'
  }
];

// Keep the structure ready; add objects later when achievements are available.
export const awards = [];
