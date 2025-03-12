# Analyseur Lexical

Réalisé par Peter SAAD et Maroun CHAHINE
4IF - Groupe 3

Ce projet est un analyseur lexical pour une grammaire personnalisée.

Nous avons décidé de considérer que s'il y a deux (ou plus) symboles '+', on gère l'erreur en gardant le premier (Transition de l'état 4)
Tous les autres cas d'erreur de syntaxes arrêtent l'analyse, en indiquant les symboles attendus et le symbole reçu


Il faut d'abord faire un 'make' dans le dossier courant puis exécuter la commande './go'

Les étapes sont indiquées par le code à partir d'ici.

Nous avons décidé d'implémenter plusieurs classes Expression pour réaliser éventuellement l'arbre d'analyse (non effectué) au lieu d'avoir uniquement une seule classe Expr.
C'est pour cela que nous avons les classes Symbole, Expr, ExprBin, ExprPlus, ExprMult et ExprVal.