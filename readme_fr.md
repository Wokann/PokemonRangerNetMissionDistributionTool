## 宝可梦巡护员网络任务配信器
Pokemon Ranger Net Mission Distribution Tool (PRNMDTool)<br>
卧看微尘制作（made by wokann）<br>
Code source : https://github.com/Wokann/PokemonRangerNetMissionDistributionTool <br>
Cet outil propose actuellement trois interfaces linguistiques (chinois, anglais, français) (il prend également en charge l'ajout d'autres langues, voir i18n.h pour plus de détails)

## Fonctionnalités
1. Distribuer des missions Ranger Net pour Ranger 1 (jp), Ranger 2 (jp et international), Ranger 3 (jp et international) sur des sauvegardes ayant déjà une progression de jeu.
2. Créer des fichiers de sauvegarde initiaux contenant des missions pour Ranger 1 (jp), Ranger 2 (jp et international), Ranger 3 (jp et international).
3. Réinitialiser la mission Manaphy de Ranger 1, en remettant l'état « œuf envoyé » à « œuf non reçu » ou « œuf reçu mais non envoyé ». (Supporte actuellement Ranger 1 jp et international)

## Utilisation
1. Glissez le(s) fichier(s) de sauvegarde directement sur PRNMDTool.exe, plusieurs fichiers simultanément sont supportés. (Correspond aux fonctionnalités 1 et 3)
2. Via la ligne de commande. (Correspond aux fonctionnalités 1 et 3)
```
PRNMDTool.exe [fichier1] [fichier2] [fichier3] ...
```
3. Double-cliquez sur PRNMDTool.exe pour générer une sauvegarde initiale de distribution. (Correspond à la fonctionnalité 2)

## Remerciements
1. Déchiffrement/chiffrement de la sauvegarde Ranger 1 et recherche mémoire : @ajxpk @BlackShark @DeadSkullzJr

## Références
1. https://projectpokemon.org/home/forums/topic/45846-pokemon-ranger-save-file-encryption/#replyForm
2. https://projectpokemon.org/home/forums/topic/6785-codes-for-pokemon-ranger-1-and-2/
3. https://projectpokemon.org/home/files/file/1933-pokemon-ranger-blank-mission-saves/
