# Portfolio — Omar Dahman

Site portfolio statique (HTML/CSS/JS pur), hébergé gratuitement sur GitHub Pages.

## Structure

- `index.html` — contenu du site
- `styles.css` — styles (thème clair/sombre automatique + bouton de bascule)
- `script.js` — bascule de thème, année du footer
- `assets/CV_Omar_DAHMAN.pdf` — CV téléchargeable

## Développement local

Ouvrir `index.html` dans un navigateur, ou lancer un petit serveur local :

```
python -m http.server 8000
```

puis aller sur http://localhost:8000

## Déploiement sur GitHub Pages (gratuit)

1. Créer un dépôt GitHub (ex: `portfolio`).
2. Depuis ce dossier :
   ```
   git remote add origin https://github.com/<ton-user>/portfolio.git
   git branch -M main
   git push -u origin main
   ```
3. Sur GitHub : Settings → Pages → Source: "Deploy from a branch" → Branch: `main` / `root`.
4. Le site sera disponible sur `https://<ton-user>.github.io/portfolio/` après 1-2 minutes.

Pour un domaine personnalisé plus tard, ajouter un fichier `CNAME` et configurer les DNS chez le registrar (compter ~10€/an pour un nom de domaine, l'hébergement reste gratuit).
