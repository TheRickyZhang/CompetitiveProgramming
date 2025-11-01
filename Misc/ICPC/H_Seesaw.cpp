import React, { useEffect, useRef, useState } from "react";

type Item = {
  href: string;
  title: string;
  description: string;
  languages: string[];
  libraries: string[];
  tools: string[];
};

const DEMO_ITEMS: Item[] = [
  {
    href: "#", title: "Dashboard", description: "Data viz",
    languages: ["TypeScript", "Python"], libraries: ["React", "Three.js"], tools: ["Git"],
  },
  {
    href: "#", title: "Game Engine", description: "3D engine",
    languages: ["C++"], libraries: ["Three.js"], tools: ["Git"],
  },
  {
    href: "#", title: "Portfolio", description: "Website",
    languages: ["TypeScript"], libraries: ["React"], tools: ["Astro", "Git"],
  },
  {
    href: "#", title: "ML Pipeline", description: "Data pipeline",
    languages: ["Python"], libraries: [], tools: ["Git"],
  },
];

export default function SkillsGraph({ items = DEMO_ITEMS }: { items?: Item[] }) {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [selected, setSelected] = useState<any>(null);

  useEffect(() => {
    const canvas = canvasRef.current;
    if (!canvas) return;

    const ctx = canvas.getContext("2d");
    if (!ctx) return;

    const W = 800;
    const H = 500;
    canvas.width = W;
    canvas.height = H;

    // Build nodes
    const skillMap = new Map<string, any>();
    
    items.forEach(item => {
      const allSkills = [...item.languages, ...item.libraries, ...item.tools];
      allSkills.forEach(skill => {
        if (!skillMap.has(skill)) {
          skillMap.set(skill, {
            name: skill,
            count: 0,
            projects: [],
            x: Math.random() * W,
            y: Math.random() * H,
            vx: (Math.random() - 0.5) * 2,
            vy: (Math.random() - 0.5) * 2,
          });
        }
        const node = skillMap.get(skill)!;
        node.count++;
        node.projects.push(item);
      });
    });

    const nodes = Array.from(skillMap.values());

    // Build edges
    const edges: Array<[string, string]> = [];
    items.forEach(item => {
      const skills = [...item.languages, ...item.libraries, ...item.tools];
      for (let i = 0; i < skills.length; i++) {
        for (let j = i + 1; j < skills.length; j++) {
          edges.push([skills[i], skills[j]]);
        }
      }
    });

    let frame = 0;
    const animate = () => {
      frame++;

      // Physics - repulsion
      for (let i = 0; i < nodes.length; i++) {
        for (let j = i + 1; j < nodes.length; j++) {
          const dx = nodes[i].x - nodes[j].x;
          const dy = nodes[i].y - nodes[j].y;
          const dist = Math.max(Math.sqrt(dx * dx + dy * dy), 1);
          const force = 500 / (dist * dist);
          
          nodes[i].vx += (dx / dist) * force;
          nodes[i].vy += (dy / dist) * force;
          nodes[j].vx -= (dx / dist) * force;
          nodes[j].vy -= (dy / dist) * force;
        }
      }

      // Attraction along edges
      edges.forEach(([a, b]) => {
        const nodeA = nodes.find(n => n.name === a);
        const nodeB = nodes.find(n => n.name === b);
        if (!nodeA || !nodeB) return;

        const dx = nodeB.x - nodeA.x;
        const dy = nodeB.y - nodeA.y;
        const dist = Math.max(Math.sqrt(dx * dx + dy * dy), 1);
        const force = 0.005 * (dist - 100);

        nodeA.vx += (dx / dist) * force;
        nodeA.vy += (dy / dist) * force;
        nodeB.vx -= (dx / dist) * force;
        nodeB.vy -= (dy / dist) * force;
      });

      // Update positions
      nodes.forEach(node => {
        // Center pull
        node.vx += (W / 2 - node.x) * 0.0008;
        node.vy += (H / 2 - node.y) * 0.0008;

        // Damping
        node.vx *= 0.92;
        node.vy *= 0.92;

        // Cap velocity
        const speed = Math.sqrt(node.vx * node.vx + node.vy * node.vy);
        if (speed > 3) {
          node.vx = (node.vx / speed) * 3;
          node.vy = (node.vy / speed) * 3;
        }

        // Move
        node.x += node.vx;
        node.y += node.vy;

        // Bounce
        const r = 20 + node.count * 3;
        if (node.x < r) { node.x = r; node.vx = Math.abs(node.vx); }
        if (node.x > W - r) { node.x = W - r; node.vx = -Math.abs(node.vx); }
        if (node.y < r) { node.y = r; node.vy = Math.abs(node.vy); }
        if (node.y > H - r) { node.y = H - r; node.vy = -Math.abs(node.vy); }
      });

      // Clear canvas
      ctx.fillStyle = "#ffffff";
      ctx.fillRect(0, 0, W, H);

      // Draw edges
      ctx.strokeStyle = "rgba(150, 150, 150, 0.2)";
      ctx.lineWidth = 2;
      edges.forEach(([a, b]) => {
        const nodeA = nodes.find(n => n.name === a);
        const nodeB = nodes.find(n => n.name === b);
        if (!nodeA || !nodeB) return;

        ctx.beginPath();
        ctx.moveTo(nodeA.x, nodeA.y);
        ctx.lineTo(nodeB.x, nodeB.y);
        ctx.stroke();
      });

      // Draw nodes
      nodes.forEach(node => {
        const r = 20 + node.count * 3;
        
        // Circle
        ctx.beginPath();
        ctx.arc(node.x, node.y, r, 0, Math.PI * 2);
        ctx.fillStyle = "#ffffff";
        ctx.fill();
        ctx.strokeStyle = selected?.name === node.name ? "#3b82f6" : "#333333";
        ctx.lineWidth = selected?.name === node.name ? 3 : 2;
        ctx.stroke();

        // Text
        ctx.fillStyle = "#000000";
        ctx.font = "bold 11px sans-serif";
        ctx.textAlign = "center";
        ctx.textBaseline = "middle";
        const text = node.name.length > 10 ? node.name.slice(0, 9) + "…" : node.name;
        ctx.fillText(text, node.x, node.y);
      });

      requestAnimationFrame(animate);
    };

    const animationId = requestAnimationFrame(animate);

    // Click handler
    const handleClick = (e: MouseEvent) => {
      const rect = canvas.getBoundingClientRect();
      const x = e.clientX - rect.left;
      const y = e.clientY - rect.top;

      let found = null;
      for (const node of nodes) {
        const r = 20 + node.count * 3;
        const dist = Math.sqrt((x - node.x) ** 2 + (y - node.y) ** 2);
        if (dist < r) {
          found = node;
          break;
        }
      }
      setSelected(found);
    };

    canvas.addEventListener("click", handleClick);

    return () => {
      cancelAnimationFrame(animationId);
      canvas.removeEventListener("click", handleClick);
    };
  }, [items, selected]);

  return (
    <div style={{ position: "relative", width: 800, height: 500, margin: "0 auto" }}>
      <canvas
        ref={canvasRef}
        style={{ 
          border: "1px solid #ddd", 
          borderRadius: 8, 
          display: "block",
          background: "#fff"
        }}
      />
      {selected && (
        <div style={{
          position: "absolute",
          bottom: 16,
          left: 16,
          right: 16,
          background: "white",
          border: "1px solid #ddd",
          borderRadius: 8,
          padding: 16,
          boxShadow: "0 4px 12px rgba(0,0,0,0.15)",
        }}>
          <div style={{ display: "flex", justifyContent: "space-between", alignItems: "center", marginBottom: 12 }}>
            <h3 style={{ margin: 0, fontSize: 18 }}>{selected.name}</h3>
            <button 
              onClick={() => setSelected(null)} 
              style={{ 
                padding: "6px 12px", 
                background: "#f3f4f6",
                border: "1px solid #d1d5db",
                borderRadius: 6,
                cursor: "pointer",
                fontWeight: 600
              }}
            >
              Close
            </button>
          </div>
          <p style={{ margin: "0 0 12px", color: "#666" }}>
            Used in {selected.count} project{selected.count !== 1 ? "s" : ""}
          </p>
          <div style={{ display: "flex", flexDirection: "column", gap: 8 }}>
            {selected.projects.map((p: Item, i: number) => (
              <div key={i} style={{ 
                padding: 8, 
                background: "#f9fafb",
                borderRadius: 6,
                fontSize: 14
              }}>
                <strong>{p.title}</strong> — {p.description}
              </div>
            ))}
          </div>
        </div>
      )}
    </div>
  );
}
