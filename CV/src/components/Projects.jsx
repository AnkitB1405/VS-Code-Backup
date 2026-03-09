import { FaArrowUpRightFromSquare, FaGithub } from 'react-icons/fa6';
import SectionTitle from './SectionTitle';
import { projects } from '../data/siteData';

const Projects = () => {
  return (
    <section id="projects" className="section-shell">
      <SectionTitle
        eyebrow="Projects"
        title="Selected work that blends product thinking and engineering"
        description="Each project focuses on UX clarity, maintainable architecture, and measurable outcomes."
      />
      <div className="grid gap-6 md:grid-cols-2 xl:grid-cols-3">
        {projects.map((project) => (
          <article
            key={project.title}
            className="group rounded-3xl border border-white/10 bg-gradient-to-b from-panel to-slate-900 p-6 shadow-card transition duration-300 hover:-translate-y-1 hover:border-cyan/50"
          >
            <h3 className="font-display text-xl text-white">{project.title}</h3>
            <p className="mt-4 text-sm leading-6 text-slate-300">{project.description}</p>

            <ul className="mt-5 flex flex-wrap gap-2">
              {project.techStack.map((tech) => (
                <li key={tech} className="rounded-full border border-white/15 px-3 py-1 text-xs text-slate-200">
                  {tech}
                </li>
              ))}
            </ul>

            <div className="mt-6 flex gap-4 text-sm">
              <a
                href={project.github}
                target="_blank"
                rel="noreferrer"
                className="inline-flex items-center gap-2 text-cyan transition hover:text-mint"
              >
                <FaGithub aria-hidden="true" /> GitHub
              </a>
              <a
                href={project.demo}
                target="_blank"
                rel="noreferrer"
                className="inline-flex items-center gap-2 text-electric transition group-hover:text-cyan"
              >
                <FaArrowUpRightFromSquare aria-hidden="true" /> Demo
              </a>
            </div>
          </article>
        ))}
      </div>
    </section>
  );
};

export default Projects;
