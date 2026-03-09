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
    'CTF Problem Solving',
    'Homelab & Self-Hosted Systems',
    'Linux & Security Workflows'
  ]
};

export const education = {
  university: 'PES University EC Campus',
  degree:
    'B.Tech in Computer Science and Engineering (Artificial Intelligence and Machine Learning)',
  duration: '2024 - 2028'
};

export const skills = {
  programmingLanguages: ['Python', 'C', 'JavaScript', 'Bash / Shell', 'Powershell'],
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
      'Personal homelab environment used for experimentation with self-hosted services, containers, networking setups, and development workflows.',
    techStack: ['Linux', 'Docker', 'Networking'],
    github: '',
    demo: ''
  },
  {
    title: 'LifeHub',
    description:
      'A student activity, budgeting, and progress tracking application designed to help students manage tasks, finances, and personal productivity.',
    techStack: ['JavaScript', 'HTML5'],
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
