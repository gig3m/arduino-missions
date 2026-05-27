// Render a standalone HTML file to PDF via the installed Chrome (puppeteer-core),
// adding a footer: "<label> · page N of M". Chrome is used (not wkhtmltopdf) so the
// section-marker emoji render; the footer's page numbers come from Chrome's own
// header/footer templates.
//
// Usage: CHROME_BIN=/path/to/chrome node tools/html2pdf.js <in.html> <out.pdf> "<footer label>"
const puppeteer = require('puppeteer-core');

const [, , htmlPath, outPath, label = ''] = process.argv;
const exe = process.env.CHROME_BIN;

if (!htmlPath || !outPath) {
  console.error('usage: node html2pdf.js <in.html> <out.pdf> "<footer label>"');
  process.exit(2);
}
if (!exe) {
  console.error('CHROME_BIN must point to a Chrome/Chromium executable');
  process.exit(2);
}

const esc = (s) => s.replace(/&/g, '&amp;').replace(/</g, '&lt;').replace(/>/g, '&gt;');
const footer = `<div style="font-size:8px; width:100%; margin:0 1.2cm; text-align:center; color:#777; font-family:sans-serif;">`
  + `${esc(label)} &nbsp;&middot;&nbsp; page <span class="pageNumber"></span> of <span class="totalPages"></span></div>`;

(async () => {
  const browser = await puppeteer.launch({ executablePath: exe, headless: 'new', args: ['--no-sandbox'] });
  try {
    const page = await browser.newPage();
    await page.goto('file://' + htmlPath, { waitUntil: 'load' });
    await page.pdf({
      path: outPath,
      format: 'Letter',
      printBackground: true,
      displayHeaderFooter: true,
      headerTemplate: '<div></div>',
      footerTemplate: footer,
      margin: { top: '1.2cm', bottom: '1.5cm', left: '1.2cm', right: '1.2cm' },
    });
  } finally {
    await browser.close();
  }
})().catch((e) => { console.error(e); process.exit(1); });
