<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>My Personal Planner</title>
<link rel="manifest" href="manifest.json">
<meta name="theme-color" content="#8C6F4B">
<link rel="apple-touch-icon" href="icon-192.png">
<meta name="apple-mobile-web-app-capable" content="yes">
<meta name="apple-mobile-web-app-status-bar-style" content="black-translucent">
<meta name="apple-mobile-web-app-title" content="studytime">
<link rel="preconnect" href="https://fonts.googleapis.com">
<link href="https://fonts.googleapis.com/css2?family=Fredoka:wght@400;500;600;700&family=Playfair+Display:ital,wght@0,600;1,600&family=Caveat:wght@600;700&display=swap" rel="stylesheet">
<style>
  :root{
    --beige:#C9AF8B;
    --beige-dark:#8C6F4B;
    --beige-pale:#F2E9DC;
    --berry:#C66F80;
    --pink:#F4C7D0;
    --pink-pale:#FCEBF1;
    --green-dark:#4A6644;
    --green:#9FAA74;
    --green-pale:#D7DAB3;
    --cream:#ECE3D2;
    --bg:#F7F1E6;
    --surface:#FFFFFF;
    --ink:#3B372E;
    --muted:#8A8271;
    --border:#E7DFCD;
    --radius:16px;
  }
  *{box-sizing:border-box;}
  body{
    margin:0;
    font-family:'Fredoka',sans-serif;
    background:var(--bg);
    color:var(--ink);
    position:relative;
  }
  h2,h3{
    font-family:'Fredoka',sans-serif;
    font-weight:600;
    margin:0 0 10px 0;
    color:var(--beige-dark);
  }
  #app{ display:block; min-height:100vh; position:relative; z-index:1; }

  /* ---------- BACKGROUND STICKERS ---------- */
  .bg-doodles{
    position:fixed; inset:0; z-index:0; pointer-events:none; overflow:hidden;
  }
  .bg-doodles .doodle{
    position:absolute;
    filter:drop-shadow(2px 4px 5px rgba(90,68,38,0.18));
  }
  .bg-doodles .doodle svg{ display:block; width:100%; height:100%; }
  .bg-doodles .doodle.faint{ opacity:0.5; }
  @media (max-width:900px){ .bg-doodles{ display:none; } }

  /* ---------- TOP NAV ---------- */
  #topnav{
    background:var(--beige-dark);
    color:#fff;
    padding:14px 30px;
    display:flex;
    align-items:center;
    justify-content:space-between;
    flex-wrap:wrap;
    gap:12px;
    position:relative; z-index:2;
  }
  .logo{ line-height:1.1; flex-shrink:0; }
  .logo .part1{
    font-family:'Playfair Display', serif;
    font-style:italic;
    font-weight:600;
    font-size:1.4rem;
    color:var(--beige-pale);
  }
  .logo .part2{
    font-family:'Caveat', cursive;
    font-weight:700;
    font-size:1.9rem;
    color:var(--pink);
    margin-left:4px;
  }
  .nav-buttons{ display:flex; flex-wrap:wrap; gap:4px; }
  .nav-btn{
    display:inline-block;
    background:none;
    border:none;
    color:#F2EAE0;
    padding:9px 16px;
    font-family:'Fredoka',sans-serif;
    font-size:0.9rem;
    font-weight:500;
    cursor:pointer;
    border-radius:999px;
  }
  .nav-btn:hover{ background:rgba(255,255,255,0.12); }
  .nav-btn.active{
    background:rgba(255,255,255,0.18);
    color:#fff;
    font-weight:600;
  }

  #content{ padding:32px 40px; max-width:1100px; margin:0 auto; position:relative; z-index:1; }
  .view{ display:none; }
  .view.active{ display:block; }
  .datebar{ color:var(--muted); margin-bottom:22px; font-size:0.95rem; }

  /* ---------- GENERIC CARD (Today / Events) ---------- */
  .card{
    background:var(--surface);
    border:1px solid var(--border);
    border-radius:var(--radius);
    padding:16px 20px;
    margin-bottom:12px;
  }
  .card.overdue{ border-color:var(--berry); background:var(--pink-pale); }
  .card-title{ font-weight:600; font-size:1.02rem; }
  .card-meta{ color:var(--muted); font-size:0.85rem; margin-top:2px; }
  .tag{
    display:inline-block; font-size:0.7rem; padding:3px 10px; border-radius:20px;
    background:var(--green-pale); color:var(--green-dark); margin-left:6px; font-weight:600;
  }
  .tag.overdue-tag{ background:var(--berry); color:#fff; }
  .tag.done-tag{ background:var(--beige-dark); color:#fff; }
  .row{ display:flex; justify-content:space-between; align-items:flex-start; gap:10px; }
  .actions{ display:flex; gap:8px; flex-shrink:0; align-items:center; }
  .empty{ color:var(--muted); font-style:italic; padding:10px 0; }

  /* ---------- BUTTONS / FORMS ---------- */
  button{ font-family:'Fredoka',sans-serif; cursor:pointer; }
  .btn{
    background:var(--berry); color:#fff; border:none; padding:9px 16px;
    border-radius:999px; font-size:0.85rem; font-weight:600;
  }
  .btn:hover{ background:#b45c6d; }
  .btn.secondary{ background:none; color:var(--muted); border:1px solid var(--border); }
  .btn.secondary:hover{ color:var(--ink); border-color:var(--ink); }
  .btn.danger{ background:none; color:var(--berry); border:1px solid var(--berry); padding:5px 11px; font-size:0.74rem;}
  .btn.danger:hover{ background:var(--berry); color:#fff; }
  .btn.small{ padding:6px 12px; font-size:0.76rem; }

  /* Compact, collapsible "add" forms so saved data stays the star of the page */
  .add-toggle{ margin-bottom:18px; }
  .add-toggle summary{
    list-style:none; cursor:pointer; display:inline-flex; align-items:center; gap:6px;
    background:var(--surface); color:var(--beige-dark); border:1px dashed var(--beige);
    padding:7px 14px; border-radius:999px; font-size:0.8rem; font-weight:600; width:fit-content;
  }
  .add-toggle summary::-webkit-details-marker{ display:none; }
  .add-toggle summary::marker{ content:''; }
  .add-toggle summary:hover{ border-color:var(--berry); color:var(--berry); }
  .add-toggle[open] summary{ margin-bottom:8px; background:var(--beige-pale); }

  form.inline-form{
    background:var(--surface); border:1px solid var(--border); border-radius:12px;
    padding:12px 14px; margin-bottom:4px; display:grid; gap:8px;
  }
  form.inline-form.two-col{ grid-template-columns:1fr 1fr; }
  form.inline-form.two-col .full{ grid-column:1/-1; }
  label{ font-size:0.7rem; color:var(--muted); display:block; margin-bottom:3px; font-weight:600; text-transform:uppercase; letter-spacing:0.3px; }
  input[type=text], input[type=date], input[type=time], input[type=number], select, textarea{
    width:100%; padding:6px 10px; border:1px solid var(--border); border-radius:8px;
    font-family:'Fredoka',sans-serif; font-size:0.82rem; background:#fffdfa;
  }
  form.inline-form .btn{ padding:7px 14px; font-size:0.8rem; }
  .section-head{ display:flex; justify-content:space-between; align-items:center; margin-bottom:10px; }

  /* ---------- WEEKLY CALENDAR (CLASS SCHEDULE) ---------- */
  .cal-wrap{
    background:var(--surface); border:1px solid var(--border); border-radius:var(--radius);
    overflow-x:auto; padding:14px 14px 20px 14px;
  }
  .cal-grid{ display:grid; grid-template-columns:56px repeat(7, minmax(112px,1fr)); min-width:900px; }
  .cal-head{
    text-align:center; padding:8px 4px 12px 4px; font-weight:700; font-size:0.78rem;
    color:var(--beige-dark); letter-spacing:0.3px;
  }
  .cal-corner{ }
  .cal-body{ display:contents; }
  .cal-timecol{ position:relative; }
  .cal-time{
    position:absolute; right:8px; font-size:0.68rem; color:var(--muted); transform:translateY(-50%);
  }
  .cal-daytrack{
    position:relative; border-left:1px solid var(--border); background:
      repeating-linear-gradient(to bottom, transparent, transparent 43px, var(--border) 44px);
  }
  .cal-event{
    position:absolute; left:4px; right:4px; border-radius:9px; padding:4px 8px;
    font-size:0.7rem; line-height:1.25; overflow:hidden;
  }
  .cal-event b{ display:block; font-size:0.74rem; }
  .cal-empty-note{ color:var(--muted); font-style:italic; font-size:0.85rem; padding:14px 4px; }

  /* ---------- PILL LIST (TO-DO / HABITS, GOALS) ---------- */
  .pill{
    display:flex; align-items:center; gap:16px;
    border-radius:20px; padding:17px 22px 17px 16px; margin-bottom:12px;
    border:1.5px solid rgba(140,111,75,0.38);
  }
  .pill.overdue{ box-shadow:inset 0 0 0 2px var(--berry); }
  .pill-bullet{
    width:40px; height:40px; border-radius:50%; flex-shrink:0;
    background:#fff; border:2.5px solid var(--berry); cursor:pointer;
    display:flex; align-items:center; justify-content:center; overflow:hidden;
    font-size:1.15rem;
  }
  .pill-bullet.filled{ background:var(--berry); color:#fff; }
  .pill-bullet img{ width:100%; height:100%; object-fit:cover; }
  .pill-body{ flex:1; min-width:0; }
  .pill-title{ font-weight:600; font-size:1.05rem; color:var(--ink); }
  .pill-meta{ font-size:0.82rem; color:#6B6350; margin-top:2px; font-weight:500; }
  .pill-actions{ display:flex; gap:8px; align-items:center; flex-shrink:0; }
  .upload-link{
    background:#fff; border:1px solid var(--berry); color:var(--berry);
    padding:6px 12px; border-radius:999px; font-size:0.76rem; font-weight:600;
  }
  .upload-link:hover{ background:var(--berry); color:#fff; }

  /* ---------- GOAL CARDS ---------- */
  .goal-card{
    background:var(--surface); border-radius:var(--radius); padding:16px 20px;
    margin-bottom:14px; border:1px solid var(--border); border-left:6px solid var(--star-color, var(--berry));
  }
  .goal-top{ display:flex; justify-content:space-between; align-items:flex-start; gap:10px; }
  .goal-star{ font-size:1.1rem; margin-right:6px; }
  .gallery{ display:flex; flex-wrap:wrap; gap:8px; margin-top:12px; }
  .gallery-item{ text-align:center; }
  .gallery-item img{ width:66px; height:66px; object-fit:cover; border-radius:10px; border:1px solid var(--border); }
  .gallery-item span{ display:block; font-size:0.65rem; color:var(--muted); margin-top:2px; }

  /* ---------- AUTH SCREEN ---------- */
  #auth-screen{
    position:fixed; inset:0; background:var(--bg); z-index:100;
    display:flex; align-items:center; justify-content:center; padding:20px;
  }
  #auth-screen.hidden{ display:none; }
  .auth-card{
    background:var(--surface); border:1px solid var(--border); border-radius:var(--radius);
    padding:34px 32px; width:100%; max-width:360px; text-align:center;
    box-shadow:0 10px 30px rgba(90,68,38,0.12);
  }
  .auth-card .logo{ display:block; margin-bottom:18px; }
  .auth-card .logo .part1{ color:var(--beige-dark); }
  .auth-card h2{ margin-bottom:4px; }
  .auth-sub{ color:var(--muted); font-size:0.85rem; margin-bottom:20px; }
  .auth-card label{ text-align:left; }
  .auth-card input{ margin-bottom:12px; }
  .auth-error{ color:var(--berry); font-size:0.8rem; min-height:18px; margin-bottom:6px; }
  .auth-toggle{ margin-top:16px; font-size:0.83rem; color:var(--muted); }
  .auth-toggle a{ color:var(--berry); font-weight:600; cursor:pointer; text-decoration:none; }
  #app.hidden{ display:none; }
  #signout-btn{
    background:none; border:1px solid rgba(255,255,255,0.4); color:#F2EAE0;
    padding:7px 14px; border-radius:999px; font-size:0.8rem;
  }
  #signout-btn:hover{ background:rgba(255,255,255,0.12); }
  #notif-btn{
    background:none; border:1px solid rgba(255,255,255,0.4); color:#F2EAE0;
    padding:7px 14px; border-radius:999px; font-size:0.8rem;
  }
  #notif-btn:hover{ background:rgba(255,255,255,0.12); }
  #notif-btn.on{ background:var(--pink); color:var(--beige-dark); border-color:var(--pink); font-weight:600; }
  #install-btn{
    background:var(--pink); color:var(--beige-dark); border:none; font-weight:600;
    padding:7px 14px; border-radius:999px; font-size:0.8rem; display:none;
  }
  #install-btn.show{ display:inline-block; }

  /* ---------- MODAL ---------- */
  .modal-backdrop{ position:fixed; inset:0; background:rgba(60,47,29,0.35); display:flex; align-items:center; justify-content:center; z-index:50; }
  .modal-backdrop.hidden{ display:none; }
  .modal{ background:#fff; border-radius:var(--radius); padding:26px 26px; max-width:420px; width:90%; max-height:80vh; overflow:auto; border:2px solid var(--pink); }
  .modal h2{ color:var(--berry); font-family:'Fredoka',sans-serif; }
  .modal ul{ padding-left:18px; margin:10px 0; }
  .modal li{ margin-bottom:6px; }

  /* ---------- PROFILE CARD (Today) — left side, bigger photo ---------- */
  .today-layout{ display:flex; gap:26px; align-items:flex-start; flex-wrap:wrap; }
  .profile-card{
    position:relative;
    width:250px; flex-shrink:0; background:var(--surface); border:1px solid var(--border);
    border-radius:var(--radius); padding:24px 20px; text-align:center;
    overflow:hidden;
  }
  .profile-card::after{
    content:''; position:absolute; right:-26px; bottom:-26px; width:110px; height:110px;
    background:var(--beige-pale); border-radius:50%; opacity:0.6; z-index:0;
  }
  .profile-photo{
    position:relative; z-index:1;
    width:170px; height:170px; border-radius:50%; margin:0 auto 18px auto;
    background:var(--beige-pale); border:5px solid var(--beige);
    box-shadow:0 0 0 4px var(--pink-pale);
    display:flex; align-items:center; justify-content:center; overflow:hidden;
    cursor:pointer; font-size:2rem; color:var(--beige-dark);
  }
  .profile-photo img{ width:100%; height:100%; object-fit:cover; }
  .profile-fields{ position:relative; z-index:1; text-align:left; }
  .profile-fields label{ margin-top:12px; }
  .profile-fields label:first-child{ margin-top:0; }
  .profile-name-field input{ font-size:1.1rem; font-weight:600; font-family:'Fredoka',sans-serif; }
  .today-main{ flex:1; min-width:280px; }

  @media (max-width:760px){
    #topnav{ padding:12px 16px; justify-content:center; }
    .nav-buttons{ justify-content:center; width:100%; }
    #content{ padding:20px; }
    form.inline-form.two-col{ grid-template-columns:1fr; }
    .today-layout{ flex-direction:column; }
    .profile-card{ width:100%; }
  }
</style>
</head>
<body>

<!-- decorative beige coffee / book / notebook stickers (filled illustration style) -->
<div class="bg-doodles" aria-hidden="true">

  <!-- to-go coffee cup, top-left -->
  <div class="doodle" style="top:78px; left:14px; width:120px; height:120px; transform:rotate(-10deg);">
    <svg viewBox="0 0 100 100">
      <path d="M22 46c1-3 4-4 6-4h44c2 0 5 1 6 4l-6 40a7 7 0 01-7 6H35a7 7 0 01-7-6z" fill="#C9AF8B"/>
      <path d="M20 40h60l-2 10H22z" fill="#8C6F4B"/>
      <rect x="30" y="52" width="40" height="10" rx="3" fill="#F2E9DC" opacity="0.85"/>
      <path d="M38 20c-2 4 3 6 1 10M50 18c-2 4 3 6 1 10M62 20c-2 4 3 6 1 10" fill="none" stroke="#8C6F4B" stroke-width="3.5" stroke-linecap="round"/>
      <path d="M60 68c3 3 3 7 0 10" fill="none" stroke="#C66F80" stroke-width="4" stroke-linecap="round"/>
      <circle cx="41" cy="78" r="3" fill="#C66F80"/>
    </svg>
  </div>

  <!-- open book, top-right -->
  <div class="doodle" style="top:56px; right:5%; width:130px; height:100px; transform:rotate(8deg);">
    <svg viewBox="0 0 120 90">
      <path d="M60 18C48 8 26 8 12 12v54c14-4 36-4 48 6z" fill="#8C6F4B"/>
      <path d="M60 18c12-10 34-10 48-6v54c-14-4-36-4-48 6z" fill="#C9AF8B"/>
      <path d="M18 22c10-3 24-3 34 3M18 34c10-3 24-3 34 3M18 46c10-3 24-3 34 3" fill="none" stroke="#F2E9DC" stroke-width="2.5" stroke-linecap="round"/>
      <path d="M102 22c-10-3-24-3-34 3M102 34c-10-3-24-3-34 3M102 46c-10-3-24-3-34 3" fill="none" stroke="#ECE3D2" stroke-width="2.5" stroke-linecap="round"/>
      <path d="M60 18v54" stroke="#6b5636" stroke-width="2"/>
      <rect x="55" y="0" width="10" height="26" fill="#C66F80"/>
      <path d="M55 26l5-6 5 6z" fill="#C66F80"/>
    </svg>
  </div>

  <!-- spiral notebook, bottom-left -->
  <div class="doodle" style="bottom:56px; left:3%; width:110px; height:130px; transform:rotate(7deg);">
    <svg viewBox="0 0 90 110">
      <rect x="18" y="8" width="64" height="94" rx="8" fill="#C9AF8B"/>
      <rect x="26" y="18" width="48" height="74" rx="3" fill="#F7F1E6"/>
      <path d="M32 32h32M32 42h32M32 52h32M32 62h24" stroke="#C9AF8B" stroke-width="3" stroke-linecap="round"/>
      <g fill="none" stroke="#8C6F4B" stroke-width="4" stroke-linecap="round">
        <circle cx="14" cy="18" r="4.5"/><circle cx="14" cy="32" r="4.5"/><circle cx="14" cy="46" r="4.5"/>
        <circle cx="14" cy="60" r="4.5"/><circle cx="14" cy="74" r="4.5"/><circle cx="14" cy="88" r="4.5"/>
      </g>
      <path d="M66 78l4 8 9-13" fill="none" stroke="#C66F80" stroke-width="4" stroke-linecap="round" stroke-linejoin="round"/>
    </svg>
  </div>

  <!-- pencil, bottom-right -->
  <div class="doodle" style="bottom:72px; right:4%; width:120px; height:120px; transform:rotate(-18deg);">
    <svg viewBox="0 0 110 60">
      <rect x="0" y="18" width="70" height="20" fill="#C9AF8B"/>
      <rect x="0" y="18" width="70" height="6" fill="#F2E9DC" opacity="0.7"/>
      <path d="M70 18l18 10-18 10z" fill="#8C6F4B"/>
      <path d="M88 28l12 0" stroke="#3B372E" stroke-width="3" stroke-linecap="round"/>
      <rect x="-14" y="18" width="16" height="20" rx="3" fill="#C66F80"/>
      <rect x="0" y="18" width="8" height="20" fill="#ECE3D2"/>
    </svg>
  </div>

  <!-- coffee bean pair, faint mid-left -->
  <div class="doodle faint" style="top:44%; left:1%; width:80px; height:60px; transform:rotate(15deg);">
    <svg viewBox="0 0 100 70">
      <ellipse cx="35" cy="35" rx="28" ry="20" transform="rotate(-30 35 35)" fill="#8C6F4B"/>
      <path d="M18 42c8-10 8-24 26-30" fill="none" stroke="#F2E9DC" stroke-width="4" stroke-linecap="round"/>
      <ellipse cx="72" cy="42" rx="22" ry="16" transform="rotate(-20 72 42)" fill="#C9AF8B"/>
      <path d="M58 48c6-8 6-18 22-24" fill="none" stroke="#F7F1E6" stroke-width="3" stroke-linecap="round"/>
    </svg>
  </div>

  <!-- mug with heart, faint mid-right -->
  <div class="doodle faint" style="top:40%; right:2%; width:95px; height:95px; transform:rotate(-9deg);">
    <svg viewBox="0 0 100 100">
      <path d="M22 34h44v28a16 16 0 01-16 16H38a16 16 0 01-16-16z" fill="#C9AF8B"/>
      <ellipse cx="44" cy="34" rx="22" ry="7" fill="#8C6F4B"/>
      <path d="M66 42h8a10 10 0 010 20h-8" fill="none" stroke="#8C6F4B" stroke-width="5"/>
      <path d="M44 30c-3-3-8-3-9 2-1-5-6-5-9-2-4 4 3 10 9 14 6-4 13-10 9-14z" fill="#C66F80"/>
    </svg>
  </div>

  <!-- washi tape strip accent -->
  <div class="doodle faint" style="top:16px; left:42%; width:110px; height:34px; transform:rotate(-4deg);">
    <svg viewBox="0 0 140 40"><rect x="0" y="0" width="140" height="40" fill="#C9AF8B" opacity="0.8"/><rect x="0" y="0" width="140" height="40" fill="none" stroke="#F2E9DC" stroke-width="4" stroke-dasharray="2 10"/></svg>
  </div>
</div>

<!-- SIGN IN / SIGN UP SCREEN -->
<div id="auth-screen">
  <div class="auth-card">
    <div class="logo"><span class="part1">study</span><span class="part2">time</span></div>
    <h2 id="auth-title">Welcome back</h2>
    <div class="auth-sub" id="auth-sub">Sign in to open your planner</div>
    <form id="auth-form">
      <label>Email</label>
      <input type="email" id="auth-email" required autocomplete="email">
      <label>Password</label>
      <input type="password" id="auth-password" required autocomplete="current-password" minlength="6">
      <div class="auth-error" id="auth-error"></div>
      <button type="submit" class="btn" id="auth-submit-btn" style="width:100%;">Sign In</button>
    </form>
    <div class="auth-toggle">
      <span id="auth-toggle-text">Don't have an account?</span>
      <a id="auth-toggle-link">Create one</a>
    </div>
  </div>
</div>

<div id="app" class="hidden">
  <nav id="topnav">
    <div class="logo"><span class="part1">study</span><span class="part2">time</span></div>
    <div class="nav-buttons">
      <button class="nav-btn active" data-tab="today">Today</button>
      <button class="nav-btn" data-tab="classes">Class Schedule</button>
      <button class="nav-btn" data-tab="events">Calendar Events</button>
      <button class="nav-btn" data-tab="todos">To-Do / Habits</button>
      <button class="nav-btn" data-tab="goals">Goals</button>
    </div>
    <button id="install-btn">⬇ Install App</button>
    <button id="notif-btn">🔔 Enable Alerts</button>
    <button id="signout-btn">Sign Out</button>
  </nav>

  <main id="content">


    <!-- TODAY -->
    <section id="view-today" class="view active">

      <div class="today-layout">
        <aside class="profile-card">
          <div class="profile-photo" id="profile-photo-frame" onclick="triggerProfilePhoto()">
            <img id="profile-photo-img" style="display:none;">
            <span id="profile-photo-placeholder">+</span>
          </div>
          <div class="profile-fields">
            <div class="profile-name-field">
              <label>Name</label>
              <input type="text" id="profile-name" placeholder="Your name" oninput="updateProfile('name', this.value)">
            </div>
            <label>School</label>
            <input type="text" id="profile-school" placeholder="Your school" oninput="updateProfile('school', this.value)">
            <label>Age</label>
            <input type="number" id="profile-age" placeholder="Age" oninput="updateProfile('age', this.value)">
            <label>Year &amp; Course</label>
            <input type="text" id="profile-year" placeholder="e.g. 2nd Year, BSIT" oninput="updateProfile('yearCourse', this.value)">
          </div>
        </aside>
        <div class="today-main">
          <h2>Today's Planner</h2>
          <div class="datebar" id="today-datebar"></div>
          <h3>Classes Today</h3>
          <div id="today-classes"></div>
          <h3>Events Today</h3>
          <div id="today-events"></div>
          <h3>Tasks Today</h3>
          <div id="today-tasks"></div>
          <h3>Active Goals</h3>
          <div id="today-goals"></div>
        </div>
      </div>
    </section>

    <!-- CLASS SCHEDULE -->
    <section id="view-classes" class="view">
      <div class="section-head"><h2>Class Schedule</h2></div>
      <details class="add-toggle">
        <summary>+ Add Class</summary>
        <form class="inline-form two-col" id="form-class">
          <div><label>Subject</label><input type="text" id="class-subject" required></div>
          <div><label>Day</label>
            <select id="class-day">
              <option>Sunday</option><option>Monday</option><option>Tuesday</option><option>Wednesday</option>
              <option>Thursday</option><option>Friday</option><option>Saturday</option>
            </select>
          </div>
          <div><label>Start Time</label><input type="time" id="class-start" required></div>
          <div><label>End Time</label><input type="time" id="class-end" required></div>
          <div>
            <label>Color</label>
            <select id="class-color">
              <option value="pink">Pink</option>
              <option value="green">Green</option>
              <option value="blue">Blue</option>
              <option value="yellow">Yellow</option>
              <option value="red">Red</option>
            </select>
          </div>
          <div class="full"><button type="submit" class="btn">Add Class</button></div>
        </form>
      </details>
      <div class="cal-wrap" id="cal-wrap"></div>
      <div id="list-classes" style="margin-top:16px;"></div>
    </section>

    <!-- EVENTS -->
    <section id="view-events" class="view">
      <div class="section-head"><h2>Calendar Events</h2></div>
      <details class="add-toggle">
        <summary>+ Add Event</summary>
        <form class="inline-form two-col" id="form-event">
          <div><label>Event Name</label><input type="text" id="event-name" required></div>
          <div><label>Date</label><input type="date" id="event-date" required></div>
          <div><label>Time</label><input type="time" id="event-time"></div>
          <div class="full"><label>Description</label><textarea id="event-desc" rows="2"></textarea></div>
          <div class="full"><button type="submit" class="btn">Add Event</button></div>
        </form>
      </details>
      <div id="list-events"></div>
    </section>

    <!-- TODO / HABITS -->
    <section id="view-todos" class="view">
      <div class="section-head"><h2>To-Do / Habits</h2></div>
      <details class="add-toggle">
        <summary>+ Add Task / Habit</summary>
        <form class="inline-form two-col" id="form-todo">
          <div class="full"><label>Task / Habit</label><input type="text" id="todo-task" required></div>
          <div><label>Date</label><input type="date" id="todo-date" required></div>
          <div><label>Type</label>
            <select id="todo-type"><option value="todo">To-Do (needs photo proof to complete)</option><option value="habit">Habit (simple check-off)</option></select>
          </div>
          <div class="full"><button type="submit" class="btn">Add</button></div>
        </form>
      </details>
      <div id="list-todos"></div>
    </section>

    <!-- GOALS -->
    <section id="view-goals" class="view">
      <div class="section-head"><h2>Goals</h2></div>
      <details class="add-toggle">
        <summary>+ Add Goal</summary>
        <form class="inline-form two-col" id="form-goal">
          <div class="full"><label>Goal</label><input type="text" id="goal-name" required></div>
          <div><label>Duration</label><input type="number" id="goal-duration" min="1" required></div>
          <div><label>Unit</label>
            <select id="goal-unit"><option value="days">days</option><option value="weeks">weeks</option><option value="months">months</option></select>
          </div>
          <div class="full"><button type="submit" class="btn">Create Goal</button></div>
        </form>
      </details>
      <div id="list-goals"></div>
    </section>

  </main>
</div>

<div class="modal-backdrop hidden" id="notify-modal">
  <div class="modal">
    <h2 id="notify-title">Reminders</h2>
    <div id="notify-body"></div>
    <button class="btn secondary" id="notify-close" style="margin-top:10px;">Close</button>
  </div>
</div>

<script>
// ---------------- STATE ----------------
// State is now kept in sync with Firestore in real time (see the module
// script below). We no longer read/write localStorage for planner data —
// Firestore is the single source of truth, scoped to the signed-in user.
let state = { classes:[], events:[], todos:[], goals:[], profile:{} };
window.state = state;

// ---------------- PALETTE HELPERS ----------------
const ROW_COLORS = ['var(--pink-pale)','var(--green-pale)','var(--pink)','var(--cream)'];
const STAR_COLORS = ['var(--berry)','var(--beige-dark)','var(--green)','#D89AA6'];
const PASTEL_COLORS = {
  pink:   {bg:'#FADCE4', fg:'#7A3B49'},
  green:  {bg:'#DFF0D8', fg:'#3F5F3A'},
  blue:   {bg:'#DCEBFA', fg:'#2F4D6B'},
  yellow: {bg:'#FCF3CF', fg:'#7A6A1F'},
  red:    {bg:'#FADBDB', fg:'#7A3232'}
};
function colorFor(list, index){ return list[index % list.length]; }
function classColor(c){ return PASTEL_COLORS[c.color] || PASTEL_COLORS.pink; }

// ---------------- DATE HELPERS ----------------
function todayISO(){ return new Date().toISOString().slice(0,10); }
function todayDayName(){ return new Date().toLocaleDateString('en-US',{weekday:'long'}); }
function formatDate(iso){
  if(!iso) return '';
  const d = new Date(iso+'T00:00:00');
  return d.toLocaleDateString('en-US',{month:'short', day:'numeric', year:'numeric'});
}
function addDaysISO(iso, days){
  const d = new Date(iso+'T00:00:00');
  d.setDate(d.getDate()+days);
  return d.toISOString().slice(0,10);
}
function computeDeadline(startISO, duration, unit){
  let days = duration;
  if(unit==='weeks') days = duration*7;
  if(unit==='months') days = duration*30;
  return addDaysISO(startISO, days);
}
function isPast(iso){ return iso < todayISO(); }
function formatTime12(t){
  if(!t) return '';
  const [h,m] = t.split(':').map(Number);
  const period = h>=12 ? 'PM':'AM';
  const hr = ((h+11)%12)+1;
  return `${hr}:${String(m).padStart(2,'0')} ${period}`;
}

// ---------------- NAV ----------------
document.querySelectorAll('.nav-btn').forEach(btn=>{
  btn.addEventListener('click', ()=>{
    document.querySelectorAll('.nav-btn').forEach(b=>b.classList.remove('active'));
    document.querySelectorAll('.view').forEach(v=>v.classList.remove('active'));
    btn.classList.add('active');
    document.getElementById('view-'+btn.dataset.tab).classList.add('active');
  });
});

// ---------------- FILE -> BASE64 ----------------
function fileToDataURL(file){
  return new Promise((resolve, reject)=>{
    const reader = new FileReader();
    reader.onload = ()=>resolve(reader.result);
    reader.onerror = reject;
    reader.readAsDataURL(file);
  });
}

// ---------------- CLASSES ----------------
document.getElementById('form-class').addEventListener('submit', async e=>{
  e.preventDefault();
  const newClass = {
    subject: document.getElementById('class-subject').value,
    day: document.getElementById('class-day').value,
    start: document.getElementById('class-start').value,
    end: document.getElementById('class-end').value,
    color: document.getElementById('class-color').value
  };
  e.target.reset();
  try{ await window.fsAddDoc(window.fsRefs.classesCol, newClass); }
  catch(err){ console.error(err); alert('Could not save class: ' + err.message); }
});
async function deleteClass(id){
  try{ await window.fsDeleteDoc(window.fsDoc(window.db, 'users', window.currentUser.uid, 'classes', id)); }
  catch(err){ console.error(err); alert('Could not delete class: ' + err.message); }
}

const CAL_START_HOUR = 6;
const CAL_END_HOUR = 22;
const ROW_PX = 44;
const CAL_HEIGHT = (CAL_END_HOUR-CAL_START_HOUR)*ROW_PX;
const DAY_NAMES = ['Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday'];

function timeToY(t){
  const [h,m] = t.split(':').map(Number);
  let y = ((h + m/60) - CAL_START_HOUR) * ROW_PX;
  return Math.max(0, Math.min(CAL_HEIGHT, y));
}

function renderCalendar(){
  const wrap = document.getElementById('cal-wrap');
  if(state.classes.length===0){
    wrap.innerHTML = '<p class="cal-empty-note">No classes added yet — add one above and it will appear on the weekly grid.</p>';
    return;
  }
  let html = '<div class="cal-grid">';
  html += '<div class="cal-corner"></div>';
  DAY_NAMES.forEach(d=>{ html += `<div class="cal-head">${d.slice(0,3).toUpperCase()}</div>`; });

  // time label column
  html += `<div class="cal-timecol" style="height:${CAL_HEIGHT}px;">`;
  for(let h=CAL_START_HOUR; h<CAL_END_HOUR; h++){
    const label = h===12 ? '12 PM' : (h>12 ? (h-12)+' PM' : h+' AM');
    html += `<div class="cal-time" style="top:${(h-CAL_START_HOUR)*ROW_PX}px;">${label}</div>`;
  }
  html += '</div>';

  // day tracks
  DAY_NAMES.forEach(day=>{
    html += `<div class="cal-daytrack" style="height:${CAL_HEIGHT}px;">`;
    const dayClasses = state.classes.filter(c=>c.day===day);
    dayClasses.forEach((c, i)=>{
      const color = classColor(c);
      const top = timeToY(c.start);
      const height = Math.max(timeToY(c.end)-top, 24);
      html += `<div class="cal-event" style="top:${top}px; height:${height}px; background:${color.bg}; color:${color.fg};" title="Click list below to delete">
        <b>${escapeHTML(c.subject)}</b>${formatTime12(c.start)} - ${formatTime12(c.end)}
      </div>`;
    });
    html += '</div>';
  });

  html += '</div>';
  wrap.innerHTML = html;
}

function renderClasses(){
  renderCalendar();
  const el = document.getElementById('list-classes');
  if(state.classes.length===0){ el.innerHTML=''; return; }
  el.innerHTML = state.classes.map((c,i)=>{
    const color = classColor(c);
    return `<div class="pill" style="background:${color.bg};">
      <div class="pill-body">
        <div class="pill-title" style="color:${color.fg};">${escapeHTML(c.subject)}</div>
        <div class="pill-meta" style="color:${color.fg}; opacity:0.85;">${c.day} · ${formatTime12(c.start)} - ${formatTime12(c.end)}</div>
      </div>
      <div class="pill-actions"><button class="btn danger" onclick="deleteClass('${c.id}')">Delete</button></div>
    </div>`;
  }).join('');
}

// ---------------- EVENTS ----------------
document.getElementById('form-event').addEventListener('submit', async e=>{
  e.preventDefault();
  const newEvent = {
    name: document.getElementById('event-name').value,
    date: document.getElementById('event-date').value,
    time: document.getElementById('event-time').value,
    description: document.getElementById('event-desc').value
  };
  e.target.reset();
  try{ await window.fsAddDoc(window.fsRefs.eventsCol, newEvent); }
  catch(err){ console.error(err); alert('Could not save event: ' + err.message); }
});
function renderEvents(){
  const el = document.getElementById('list-events');
  if(state.events.length===0){ el.innerHTML = '<p class="empty">No events added yet.</p>'; return; }
  const sorted = [...state.events].sort((a,b)=>a.date.localeCompare(b.date));
  el.innerHTML = sorted.map(ev=>`
    <div class="card">
      <div class="row">
        <div>
          <div class="card-title">${escapeHTML(ev.name)}</div>
          <div class="card-meta">${formatDate(ev.date)}${ev.time? ' · '+formatTime12(ev.time):''}</div>
          ${ev.description? `<div class="card-meta">${escapeHTML(ev.description)}</div>`:''}
        </div>
        <div class="actions"><button class="btn danger" onclick="deleteEvent('${ev.id}')">Delete</button></div>
      </div>
    </div>`).join('');
}
async function deleteEvent(id){
  try{ await window.fsDeleteDoc(window.fsDoc(window.db, 'users', window.currentUser.uid, 'events', id)); }
  catch(err){ console.error(err); alert('Could not delete event: ' + err.message); }
}


// ---------------- TODOS / HABITS ----------------
document.getElementById('form-todo').addEventListener('submit', async e=>{
  e.preventDefault();
  const newTodo = {
    task: document.getElementById('todo-task').value,
    date: document.getElementById('todo-date').value,
    isHabit: document.getElementById('todo-type').value === 'habit',
    completed: false,
    photo: null,
    completedAt: null
  };
  e.target.reset();
  try{ await window.fsAddDoc(window.fsRefs.todosCol, newTodo); }
  catch(err){ console.error(err); alert('Could not save task: ' + err.message); }
});
async function toggleHabit(id){
  const t = state.todos.find(t=>t.id===id);
  try{
    await window.fsUpdateDoc(window.fsDoc(window.db, 'users', window.currentUser.uid, 'todos', id), { completed: !t.completed });
  }catch(err){ console.error(err); alert('Could not update habit: ' + err.message); }
}
function triggerPhotoUpload(id){
  const input = document.createElement('input');
  input.type = 'file'; input.accept = 'image/*';
  input.onchange = async ()=>{
    if(input.files && input.files[0]){
      try{
        const dataUrl = await fileToDataURL(input.files[0]);
        await window.fsUpdateDoc(window.fsDoc(window.db, 'users', window.currentUser.uid, 'todos', id), {
          photo: dataUrl, completed: true, completedAt: todayISO()
        });
      }catch(err){
        console.error(err);
        alert('Could not save photo — it may be too large. Try a smaller image. (' + err.message + ')');
      }
    }
  };
  input.click();
}
async function deleteTodo(id){
  try{ await window.fsDeleteDoc(window.fsDoc(window.db, 'users', window.currentUser.uid, 'todos', id)); }
  catch(err){ console.error(err); alert('Could not delete task: ' + err.message); }
}
function renderTodos(){
  const el = document.getElementById('list-todos');
  if(state.todos.length===0){ el.innerHTML = '<p class="empty">No tasks added yet.</p>'; return; }
  const sorted = [...state.todos].sort((a,b)=>a.date.localeCompare(b.date));
  el.innerHTML = sorted.map((t,i)=>{
    const overdue = !t.completed && isPast(t.date);
    const rowColor = colorFor(ROW_COLORS, i);
    let bullet;
    if(t.isHabit){
      bullet = `<div class="pill-bullet ${t.completed?'filled':''}" onclick="toggleHabit('${t.id}')">${t.completed?'✓':''}</div>`;
    } else if(t.completed){
      bullet = `<div class="pill-bullet filled"><img src="${t.photo}" title="Proof uploaded ${formatDate(t.completedAt)}"></div>`;
    } else {
      bullet = `<div class="pill-bullet" onclick="triggerPhotoUpload('${t.id}')" title="Upload photo proof to complete">+</div>`;
    }
    return `
    <div class="pill ${overdue?'overdue':''}" style="background:${rowColor};">
      <div onclick="${t.isHabit? `toggleHabit('${t.id}')` : (t.completed? '' : `triggerPhotoUpload('${t.id}')`)}" style="display:contents;">
      </div>
      ${bullet}
      <div class="pill-body">
        <div class="pill-title">${escapeHTML(t.task)}
          ${t.isHabit? '<span class="tag">Habit</span>':'<span class="tag">To-Do</span>'}
          ${t.completed? '<span class="tag done-tag">Done</span>':''}
          ${overdue? '<span class="tag overdue-tag">Missed</span>':''}
        </div>
        <div class="pill-meta">Due ${formatDate(t.date)}${(!t.isHabit && !t.completed) ? ' · needs photo proof to complete' : ''}</div>
      </div>
      <div class="pill-actions">
        <button class="btn danger" onclick="deleteTodo('${t.id}')">Delete</button>
      </div>
    </div>`;
  }).join('');
}

// ---------------- GOALS ----------------
document.getElementById('form-goal').addEventListener('submit', async e=>{
  e.preventDefault();
  const start = todayISO();
  const duration = parseInt(document.getElementById('goal-duration').value,10);
  const unit = document.getElementById('goal-unit').value;
  const newGoal = {
    name: document.getElementById('goal-name').value,
    duration, unit, startDate: start,
    deadline: computeDeadline(start, duration, unit),
    photos: []
  };
  e.target.reset();
  try{ await window.fsAddDoc(window.fsRefs.goalsCol, newGoal); }
  catch(err){ console.error(err); alert('Could not save goal: ' + err.message); }
});
function triggerGoalPhoto(id){
  const input = document.createElement('input');
  input.type = 'file'; input.accept = 'image/*';
  input.onchange = async ()=>{
    if(input.files && input.files[0]){
      try{
        const dataUrl = await fileToDataURL(input.files[0]);
        await window.fsUpdateDoc(
          window.fsDoc(window.db, 'users', window.currentUser.uid, 'goals', id),
          { photos: window.fsArrayUnion({ data: dataUrl, date: todayISO() }) }
        );
      }catch(err){
        console.error(err);
        alert('Could not save photo — it may be too large. Try a smaller image. (' + err.message + ')');
      }
    }
  };
  input.click();
}
async function deleteGoal(id){
  try{ await window.fsDeleteDoc(window.fsDoc(window.db, 'users', window.currentUser.uid, 'goals', id)); }
  catch(err){ console.error(err); alert('Could not delete goal: ' + err.message); }
}
function renderGoals(){
  const el = document.getElementById('list-goals');
  if(state.goals.length===0){ el.innerHTML = '<p class="empty">No goals added yet.</p>'; return; }
  el.innerHTML = state.goals.map((g,i)=>{
    const overdue = isPast(g.deadline);
    const star = colorFor(STAR_COLORS, i);
    const gallery = g.photos.length
      ? `<div class="gallery">${g.photos.map(p=>`<div class="gallery-item"><img src="${p.data}"><span>${formatDate(p.date)}</span></div>`).join('')}</div>`
      : `<p class="empty" style="padding:6px 0;">No progress photos yet.</p>`;
    return `
    <div class="goal-card" style="--star-color:${star};">
      <div class="goal-top">
        <div>
          <div class="card-title"><span class="goal-star" style="color:${star};">&#9733;</span>${escapeHTML(g.name)} ${overdue?'<span class="tag overdue-tag">Deadline passed</span>':''}</div>
          <div class="card-meta">${g.duration} ${g.unit} · Started ${formatDate(g.startDate)} · Deadline ${formatDate(g.deadline)}</div>
        </div>
        <div class="pill-actions">
          <button class="btn small" onclick="triggerGoalPhoto('${g.id}')">Add photo</button>
          <button class="btn danger" onclick="deleteGoal('${g.id}')">Delete</button>
        </div>
      </div>
      ${gallery}
    </div>`;
  }).join('');
}

// ---------------- PROFILE ----------------
let profileSaveTimer = null;
function updateProfile(field, value){
  // Debounced so we don't write to Firestore on every single keystroke.
  clearTimeout(profileSaveTimer);
  profileSaveTimer = setTimeout(async ()=>{
    try{
      await window.fsSetDoc(window.fsRefs.profileDoc, { [field]: value }, { merge: true });
    }catch(err){ console.error(err); }
  }, 400);
}
function triggerProfilePhoto(){
  const input = document.createElement('input');
  input.type = 'file'; input.accept = 'image/*';
  input.onchange = async ()=>{
    if(input.files && input.files[0]){
      try{
        const dataUrl = await fileToDataURL(input.files[0]);
        await window.fsSetDoc(window.fsRefs.profileDoc, { photo: dataUrl }, { merge: true });
      }catch(err){
        console.error(err);
        alert('Could not save photo — it may be too large. Try a smaller image. (' + err.message + ')');
      }
    }
  };
  input.click();
}
function renderProfilePhoto(){
  const img = document.getElementById('profile-photo-img');
  const placeholder = document.getElementById('profile-photo-placeholder');
  if(state.profile.photo){
    img.src = state.profile.photo;
    img.style.display = 'block';
    placeholder.style.display = 'none';
  } else {
    img.style.display = 'none';
    placeholder.style.display = 'block';
  }
}
function initProfile(){
  document.getElementById('profile-name').value = state.profile.name || '';
  document.getElementById('profile-school').value = state.profile.school || '';
  document.getElementById('profile-age').value = state.profile.age || '';
  document.getElementById('profile-year').value = state.profile.yearCourse || '';
  renderProfilePhoto();
}
window.initProfile = initProfile;
window.renderAll = renderAll;

// ---------------- TODAY VIEW ----------------
function renderToday(){
  document.getElementById('today-datebar').textContent = `${todayDayName()}, ${formatDate(todayISO())}`;

  const todayClasses = state.classes.filter(c=>c.day===todayDayName());
  document.getElementById('today-classes').innerHTML = todayClasses.length
    ? todayClasses.map(c=>`<div class="card"><div class="card-title">${escapeHTML(c.subject)}</div><div class="card-meta">${formatTime12(c.start)} - ${formatTime12(c.end)}</div></div>`).join('')
    : '<p class="empty">No classes scheduled today.</p>';

  const todayEvents = state.events.filter(ev=>ev.date===todayISO());
  document.getElementById('today-events').innerHTML = todayEvents.length
    ? todayEvents.map(ev=>`<div class="card"><div class="card-title">${escapeHTML(ev.name)}</div><div class="card-meta">${ev.time? formatTime12(ev.time):''}</div></div>`).join('')
    : '<p class="empty">No events scheduled today.</p>';

  const todayTasks = state.todos.filter(t=>t.date===todayISO());
  document.getElementById('today-tasks').innerHTML = todayTasks.length
    ? todayTasks.map(t=>`<div class="card"><div class="card-title">${escapeHTML(t.task)} ${t.completed? '<span class="tag done-tag">Done</span>':'<span class="tag">Pending</span>'}</div></div>`).join('')
    : '<p class="empty">No tasks scheduled today.</p>';

  document.getElementById('today-goals').innerHTML = state.goals.length
    ? state.goals.map(g=>`<div class="card ${isPast(g.deadline)?'overdue':''}"><div class="card-title">${escapeHTML(g.name)}</div><div class="card-meta">Deadline ${formatDate(g.deadline)}</div></div>`).join('')
    : '<p class="empty">No goals created yet.</p>';
}

// ---------------- MISSED / UPCOMING ITEM NOTIFICATIONS ----------------
function getMissedItems(){
  const missedTasks = state.todos.filter(t=>!t.completed && isPast(t.date) && !t.isHabit);
  const missedHabits = state.todos.filter(t=>!t.completed && isPast(t.date) && t.isHabit);
  const missedGoals = state.goals.filter(g=>isPast(g.deadline));
  return { missedTasks, missedHabits, missedGoals };
}
// "Due tomorrow" is the day-before heads-up. We check todos, events, and
// goal deadlines that land on tomorrow's date.
function getDueTomorrowItems(){
  const tomorrow = addDaysISO(todayISO(), 1);
  const dueTasks = state.todos.filter(t=>!t.completed && t.date===tomorrow);
  const dueEvents = state.events.filter(ev=>ev.date===tomorrow);
  const dueGoals = state.goals.filter(g=>g.deadline===tomorrow);
  return { dueTasks, dueEvents, dueGoals };
}
// Local notifications only fire while this tab/app is open (foreground) or
// backgrounded on the same device — a fully closed app needs the push
// pipeline (see the Firebase Cloud Messaging setup in the module script).
function fireLocalNotification(title, body){
  if(typeof Notification === 'undefined' || Notification.permission !== 'granted') return;
  try{
    navigator.serviceWorker && navigator.serviceWorker.ready.then(reg=>{
      reg.showNotification(title, { body, icon:'icon-192.png', badge:'icon-192.png' });
    }).catch(()=>{ new Notification(title, { body, icon:'icon-192.png' }); });
  }catch(err){ console.error('notification error', err); }
}
window.fireLocalNotification = fireLocalNotification;
// Avoid re-firing the same "due tomorrow" ping every single time data
// re-renders in one sitting (Firestore listeners can fire often).
const remindedToday = new Set();
function showNotificationsIfNeeded(){
  const { missedTasks, missedHabits, missedGoals } = getMissedItems();
  const { dueTasks, dueEvents, dueGoals } = getDueTomorrowItems();
  const totalMissed = missedTasks.length + missedHabits.length + missedGoals.length;
  const totalDue = dueTasks.length + dueEvents.length + dueGoals.length;
  if(totalMissed + totalDue === 0) return;

  let html = '';
  if(totalMissed){
    if(missedTasks.length) html += `<h3>Missed To-Do</h3><ul>${missedTasks.map(t=>`<li>${escapeHTML(t.task)} — was due ${formatDate(t.date)}</li>`).join('')}</ul>`;
    if(missedHabits.length) html += `<h3>Missed Habits</h3><ul>${missedHabits.map(t=>`<li>${escapeHTML(t.task)} — was due ${formatDate(t.date)}</li>`).join('')}</ul>`;
    if(missedGoals.length) html += `<h3>Missed Goal Deadlines</h3><ul>${missedGoals.map(g=>`<li>${escapeHTML(g.name)} — deadline was ${formatDate(g.deadline)}</li>`).join('')}</ul>`;
  }
  if(totalDue){
    if(dueTasks.length) html += `<h3>Due Tomorrow</h3><ul>${dueTasks.map(t=>`<li>${escapeHTML(t.task)}</li>`).join('')}</ul>`;
    if(dueEvents.length) html += `<h3>Events Tomorrow</h3><ul>${dueEvents.map(ev=>`<li>${escapeHTML(ev.name)}${ev.time? ' at '+formatTime12(ev.time):''}</li>`).join('')}</ul>`;
    if(dueGoals.length) html += `<h3>Goal Deadlines Tomorrow</h3><ul>${dueGoals.map(g=>`<li>${escapeHTML(g.name)}</li>`).join('')}</ul>`;
  }
  document.getElementById('notify-title').textContent = totalMissed ? 'Reminders' : 'Coming up tomorrow';
  document.getElementById('notify-body').innerHTML = html;
  document.getElementById('notify-modal').classList.remove('hidden');

  // Also fire a real system notification for tomorrow's items, once per day.
  if(totalDue){
    const key = todayISO();
    if(!remindedToday.has(key)){
      remindedToday.add(key);
      const parts = [];
      if(dueTasks.length) parts.push(`${dueTasks.length} task${dueTasks.length>1?'s':''}`);
      if(dueEvents.length) parts.push(`${dueEvents.length} event${dueEvents.length>1?'s':''}`);
      if(dueGoals.length) parts.push(`${dueGoals.length} goal deadline${dueGoals.length>1?'s':''}`);
      fireLocalNotification('Due tomorrow', parts.join(', ') + ' — check your studytime planner.');
    }
  }
}
document.getElementById('notify-close').addEventListener('click', ()=>{
  document.getElementById('notify-modal').classList.add('hidden');
});

// ---------------- UTIL ----------------
function escapeHTML(str){
  const d = document.createElement('div');
  d.textContent = str;
  return d.innerHTML;
}

// ---------------- RENDER ALL ----------------
function renderAll(){
  renderToday();
  renderClasses();
  renderEvents();
  renderTodos();
  renderGoals();
}

document.getElementById('event-date').value = todayISO();
document.getElementById('todo-date').value = todayISO();

function startPlannerApp(){
  initProfile();
  renderAll();
  showNotificationsIfNeeded();
}
window.startPlannerApp = startPlannerApp;
</script>

<script type="module">
  import { initializeApp } from "https://www.gstatic.com/firebasejs/11.0.0/firebase-app.js";
  import { getAnalytics } from "https://www.gstatic.com/firebasejs/11.0.0/firebase-analytics.js";
  import {
    getAuth, onAuthStateChanged,
    signInWithEmailAndPassword, createUserWithEmailAndPassword, signOut
  } from "https://www.gstatic.com/firebasejs/11.0.0/firebase-auth.js";
  import {
    getFirestore, collection, doc, setDoc, addDoc, updateDoc, deleteDoc,
    onSnapshot, arrayUnion
  } from "https://www.gstatic.com/firebasejs/11.0.0/firebase-firestore.js";
  import {
    getMessaging, getToken, onMessage, isSupported
  } from "https://www.gstatic.com/firebasejs/11.0.0/firebase-messaging.js";

  // Your Firebase project config
  const firebaseConfig = {
    apiKey: "AIzaSyCzlIDEKFcDt02btwvPyXzY1q_ekOiuP94",
    authDomain: "procrastinote-7658e.firebaseapp.com",
    projectId: "procrastinote-7658e",
    storageBucket: "procrastinote-7658e.firebasestorage.app",
    messagingSenderId: "352245772890",
    appId: "1:352245772890:web:5f6467082c91a040269e63",
    measurementId: "G-V8SBDG7J7Q"
  };

  const app = initializeApp(firebaseConfig);
  const analytics = getAnalytics(app);
  const auth = getAuth(app);
  const db = getFirestore(app);
  window.firebaseAuth = auth;
  window.db = db;

  // Expose Firestore functions so the classic (non-module) app script can call them
  window.fsDoc = doc;
  window.fsSetDoc = setDoc;
  window.fsAddDoc = addDoc;
  window.fsUpdateDoc = updateDoc;
  window.fsDeleteDoc = deleteDoc;
  window.fsArrayUnion = arrayUnion;

  // ---------------- PWA: INSTALL PROMPT ----------------
  // Registering the service worker is what makes Chrome/Edge/Android treat
  // this as an installable app; it also caches the shell for offline use.
  if('serviceWorker' in navigator){
    navigator.serviceWorker.register('./sw.js').then(reg=>{
      window.swRegistration = reg;
    }).catch(err=>console.error('service worker registration failed', err));
  }
  let deferredInstallPrompt = null;
  const installBtn = document.getElementById('install-btn');
  window.addEventListener('beforeinstallprompt', (e)=>{
    e.preventDefault();
    deferredInstallPrompt = e;
    installBtn.classList.add('show');
  });
  installBtn.addEventListener('click', async ()=>{
    if(!deferredInstallPrompt) return;
    deferredInstallPrompt.prompt();
    await deferredInstallPrompt.userChoice;
    deferredInstallPrompt = null;
    installBtn.classList.remove('show');
  });
  window.addEventListener('appinstalled', ()=>{ installBtn.classList.remove('show'); });

  // ---------------- PUSH NOTIFICATIONS (Firebase Cloud Messaging) ----------------
  // 1) This registers the device for push and saves a token to Firestore.
  // 2) A scheduled Cloud Function (see functions/index.js) reads that token
  //    and sends the actual "due tomorrow" push once a day — that server
  //    piece is what lets a notification arrive even with the app fully closed.
  // Get your own key from: Firebase Console → Project settings → Cloud
  // Messaging → Web Push certificates, and paste it in below.
  const VAPID_KEY = "PASTE_YOUR_VAPID_PUBLIC_KEY_HERE";

  const notifBtn = document.getElementById('notif-btn');
  let messaging = null;

  function setNotifBtnState(){
    if(typeof Notification === 'undefined') { notifBtn.style.display = 'none'; return; }
    if(Notification.permission === 'granted'){
      notifBtn.textContent = '🔔 Alerts On';
      notifBtn.classList.add('on');
    } else {
      notifBtn.textContent = '🔔 Enable Alerts';
      notifBtn.classList.remove('on');
    }
  }

  async function enableNotifications(){
    try{
      const supported = await isSupported();
      if(!supported){ alert("This browser doesn't support push notifications."); return; }
      const permission = await Notification.requestPermission();
      setNotifBtnState();
      if(permission !== 'granted') return;

      if(!messaging) messaging = getMessaging(app);
      const swReg = window.swRegistration || await navigator.serviceWorker.ready;
      const token = await getToken(messaging, { vapidKey: VAPID_KEY, serviceWorkerRegistration: swReg });
      if(token && window.currentUser){
        await setDoc(
          doc(db, 'users', window.currentUser.uid, 'meta', 'notifications'),
          { tokens: arrayUnion(token) },
          { merge: true }
        );
      }
    }catch(err){
      console.error('enableNotifications error', err);
      alert('Could not enable notifications: ' + err.message);
    }
  }
  notifBtn.addEventListener('click', enableNotifications);
  setNotifBtnState();

  // Foreground messages (app open, tab focused) — background ones are
  // handled by sw.js's onBackgroundMessage instead.
  isSupported().then(supported=>{
    if(!supported) return;
    if(!messaging) messaging = getMessaging(app);
    onMessage(messaging, (payload)=>{
      const title = (payload.notification && payload.notification.title) || 'studytime';
      const body = (payload.notification && payload.notification.body) || '';
      if(window.fireLocalNotification) window.fireLocalNotification(title, body);
    });
  }).catch(()=>{});

  let unsubscribers = [];

  function attachFirestoreListeners(uid){
    const classesCol = collection(db, 'users', uid, 'classes');
    const eventsCol  = collection(db, 'users', uid, 'events');
    const todosCol   = collection(db, 'users', uid, 'todos');
    const goalsCol   = collection(db, 'users', uid, 'goals');
    const profileDoc = doc(db, 'users', uid, 'meta', 'profile');

    window.fsRefs = { classesCol, eventsCol, todosCol, goalsCol, profileDoc };

    unsubscribers.push(onSnapshot(classesCol, snap=>{
      window.state.classes = snap.docs.map(d=>({ id:d.id, ...d.data() }));
      if(window.renderAll) window.renderAll();
    }, err=>console.error('classes listener error', err)));

    unsubscribers.push(onSnapshot(eventsCol, snap=>{
      window.state.events = snap.docs.map(d=>({ id:d.id, ...d.data() }));
      if(window.renderAll) window.renderAll();
    }, err=>console.error('events listener error', err)));

    unsubscribers.push(onSnapshot(todosCol, snap=>{
      window.state.todos = snap.docs.map(d=>({ id:d.id, ...d.data() }));
      if(window.renderAll) window.renderAll();
    }, err=>console.error('todos listener error', err)));

    unsubscribers.push(onSnapshot(goalsCol, snap=>{
      window.state.goals = snap.docs.map(d=>({ id:d.id, ...d.data() }));
      if(window.renderAll) window.renderAll();
    }, err=>console.error('goals listener error', err)));

    unsubscribers.push(onSnapshot(profileDoc, snap=>{
      window.state.profile = snap.exists() ? snap.data() : {};
      if(window.initProfile) window.initProfile();
      if(window.renderAll) window.renderAll();
    }, err=>console.error('profile listener error', err)));
  }

  function detachFirestoreListeners(){
    unsubscribers.forEach(u=>u());
    unsubscribers = [];
  }

  let mode = 'signin'; // 'signin' or 'signup'

  const authScreen = document.getElementById('auth-screen');
  const appRoot = document.getElementById('app');
  const authForm = document.getElementById('auth-form');
  const emailInput = document.getElementById('auth-email');
  const passInput = document.getElementById('auth-password');
  const errorEl = document.getElementById('auth-error');
  const submitBtn = document.getElementById('auth-submit-btn');
  const titleEl = document.getElementById('auth-title');
  const subEl = document.getElementById('auth-sub');
  const toggleText = document.getElementById('auth-toggle-text');
  const toggleLink = document.getElementById('auth-toggle-link');

  function setMode(newMode){
    mode = newMode;
    errorEl.textContent = '';
    if(mode === 'signin'){
      titleEl.textContent = 'Welcome back';
      subEl.textContent = 'Sign in to open your planner';
      submitBtn.textContent = 'Sign In';
      toggleText.textContent = "Don't have an account?";
      toggleLink.textContent = 'Create one';
    } else {
      titleEl.textContent = 'Create your account';
      subEl.textContent = 'Set a password to save your planner';
      submitBtn.textContent = 'Create Account';
      toggleText.textContent = 'Already have an account?';
      toggleLink.textContent = 'Sign in';
    }
  }
  toggleLink.addEventListener('click', ()=> setMode(mode === 'signin' ? 'signup' : 'signin'));

  function friendlyError(err){
    const code = err.code || '';
    if(code.includes('auth/invalid-email')) return "That email doesn't look right.";
    if(code.includes('auth/email-already-in-use')) return 'An account with that email already exists — try signing in instead.';
    if(code.includes('auth/weak-password')) return 'Password should be at least 6 characters.';
    if(code.includes('auth/invalid-credential') || code.includes('auth/wrong-password') || code.includes('auth/user-not-found'))
      return 'Incorrect email or password.';
    return 'Something went wrong. Please try again.';
  }

  authForm.addEventListener('submit', async (e)=>{
    e.preventDefault();
    errorEl.textContent = '';
    submitBtn.disabled = true;
    const email = emailInput.value.trim();
    const password = passInput.value;
    try{
      if(mode === 'signin'){
        await signInWithEmailAndPassword(auth, email, password);
      } else {
        await createUserWithEmailAndPassword(auth, email, password);
      }
      // onAuthStateChanged below handles showing the app
    }catch(err){
      errorEl.textContent = friendlyError(err);
    }finally{
      submitBtn.disabled = false;
    }
  });

  document.getElementById('signout-btn').addEventListener('click', ()=>{
    signOut(auth);
  });

  onAuthStateChanged(auth, (user)=>{
    if(user){
      window.currentUser = user;
      authScreen.classList.add('hidden');
      appRoot.classList.remove('hidden');
      attachFirestoreListeners(user.uid);
      if(window.startPlannerApp) window.startPlannerApp();
    } else {
      detachFirestoreListeners();
      window.currentUser = null;
      window.fsRefs = null;
      if(window.state){
        window.state.classes = []; window.state.events = [];
        window.state.todos = []; window.state.goals = []; window.state.profile = {};
      }
      appRoot.classList.add('hidden');
      authScreen.classList.remove('hidden');
      authForm.reset();
    }
  });

  setMode('signin');
</script>

</body>
</html>
