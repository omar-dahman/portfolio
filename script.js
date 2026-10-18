document.getElementById('year').textContent = new Date().getFullYear();

document.querySelectorAll('.copy-btn').forEach((btn) => {
  const label = btn.textContent;
  btn.addEventListener('click', async () => {
    try {
      await navigator.clipboard.writeText(btn.dataset.copy);
      btn.textContent = btn.dataset.done;
      setTimeout(() => { btn.textContent = label; }, 1800);
    } catch {
      window.location.href = 'mailto:' + btn.dataset.copy;
    }
  });
});
