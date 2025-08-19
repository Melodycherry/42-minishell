# 🐚 Minishell 

### Projet réalisé en collaboration avec [@Hyliah](https://github.com/Hyliah) 

Ce projet consiste à créer un **Mini Shell** simple, à l’image de Bash, pour comprendre entre autre la gestion des **processus**, des **descripteurs de fichiers** , d’un **parsing complex**, et des  **signaux**.   

## 🎯 Objectifs  

- Afficher un **prompt** et attendre la saisie de commandes.
- Gérer une **historique des commandes** fonctionnelle.
- Lancer le bon exécutable en fonction de la variable d’environnement `PATH`, ou via un chemin relatif/absolu.
- Utiliser au maximum **une seule variable globale** pour indiquer la réception d’un signal (ex : Ctrl-C).
- Gérer correctement les **quotes simples `'`** et **doubles `"`** (différences dans l’interprétation des caractères spéciaux).
- Implémenter les **redirections** :
  - `<` : redirection d’entrée
  - `>` : redirection de sortie (écrasement)
  - `>>` : redirection de sortie (ajout à la fin)
  - `<<` : here-doc avec un délimiteur
- Gérer les **pipes (`|`)** pour connecter la sortie d’une commande à l’entrée de la suivante.
- Supporter les **variables d’environnement** (`$VAR`) et l’expansion de `$?` pour récupérer le code de sortie de la dernière commande.
- Gérer les signaux :
  - `Ctrl-C` : affiche un nouveau prompt proprement.
  - `Ctrl-D` : quitte le shell.
  - `Ctrl-\` : ne fait rien.
- Implémenter les **builtins** :
  - `echo` (avec l’option `-n`)
  - `cd` (avec chemin relatif ou absolu)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`

## 📜 Limitations / Contraintes

- La fonction `readline()` peut provoquer des fuites mémoire, mais ce n’est pas demandé de les corriger.
- Votre code **doit éviter ses propres fuites mémoire**.
- Pas d’interprétation de caractères spéciaux non demandés comme `\` ou `;`.
- Une seule variable globale maximum, uniquement pour la gestion des signaux.
- Limiter le scope du projet à ce qui est demandé, prendre **bash** comme référence si un doute persiste.

---

🧠 **Ce que j’ai appris**  

• ⚙️ Gestion des processus (fork(), execve(), waitpid())  
• 🔧 Manipulation avancée des descripteurs de fichiers  
• 📝 Parsing complexe de la ligne de commande, gestion des quotes et expansions  
• 💾 Gestion de la mémoire dynamique en C et prévention des fuites  
• 🚨 Signal handling  
• 🛠️ Implémentation de commandes intégrées  
• 🔀 Gestion des pipes et redirections dans un shell  

---

✅ **STATUT:**  
📅 Date de rendu : 08.07.2025    
📝 Note obtenue : 100/100

---

