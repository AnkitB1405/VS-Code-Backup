import SectionTitle from './SectionTitle';
import { profile } from '../data/siteData';

const About = () => {
  return (
    <section id="about" className="section-shell">
      <SectionTitle
        eyebrow="About"
        title="Cybersecurity and AI learner focused on practical systems"
        description="Hands-on exploration across security, Linux, networking, and intelligent technologies."
      />

      <div className="space-y-4 rounded-2xl border border-white/10 bg-panel/70 p-6">
        {profile.aboutParagraphs.map((paragraph) => (
          <p key={paragraph} className="text-sm leading-7 text-slate-200 md:text-base">
            {paragraph}
          </p>
        ))}
      </div>

      <div className="mt-6 grid gap-4 md:grid-cols-2">
        {profile.expertise.map((item) => (
          <article
            key={item}
            className="rounded-2xl border border-white/10 bg-panel/80 p-5 transition duration-300 hover:border-cyan/60"
          >
            <p className="text-slate-100">{item}</p>
          </article>
        ))}
      </div>
    </section>
  );
};

export default About;
