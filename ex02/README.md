# Le tri de Ford-Johnson

L'algorithme de tri de Ford-Johnson est un algorithme de tri basé sur la comparaison qui a été développé pour trier une liste d'éléments en minimisant le nombre total de comparaisons nécessaires. Cet algorithme a été proposé par L. R. Ford, Jr. et D. R. Fulkerson en 1962. Il a été conçu pour être utilisé dans des situations où le coût des comparaisons est élevé.

L'idée principale derrière l'algorithme de Ford-Johnson est de minimiser le nombre de comparaisons en organisant les éléments de la liste de manière à réduire au maximum le nombre de comparaisons nécessaires pour les trier. L'algorithme fonctionne comme suit :

1. Divisez la liste d'éléments en deux sous-listes, appelées A et B, de taille égale si possible (ou presque égale si le nombre d'éléments est impair). Vous pouvez diviser la liste de manière arbitraire.

2. Triez récursivement les deux sous-listes A et B en utilisant l'algorithme de Ford-Johnson. Cela signifie que vous répétez les étapes 1 et 2 pour chaque sous-liste jusqu'à ce que chaque sous-liste soit triée.

3. Une fois que les sous-listes A et B sont triées, fusionnez-les en une seule liste triée. Cela peut être fait en comparant le premier élément de A avec le premier élément de B et en plaçant le plus petit élément dans la liste résultante. Ensuite, comparez le deuxième élément de la sous-liste d'où provient l'élément précédemment placé et ainsi de suite, jusqu'à ce que toutes les éléments soient placés dans la liste résultante.

4. La liste résultante est maintenant triée.

L'algorithme de Ford-Johnson peut sembler compliqué, mais il est basé sur le principe de la division et de la conquête, où la liste est divisée en sous-listes plus petites qui sont triées individuellement, puis fusionnées pour obtenir la liste triée finale. La clé de cet algorithme est de minimiser le nombre de comparaisons nécessaires en organisant les éléments de manière efficace.

Cet algorithme a une complexité temporelle de O(n log n), ce qui en fait un algorithme de tri relativement efficace. Cependant, il n'est généralement pas aussi rapide que des algorithmes de tri plus avancés comme le tri rapide (quicksort) ou le tri fusion (merge sort) dans la plupart des cas. Il est principalement utilisé dans des situations où le coût des comparaisons est élevé et où la réduction du nombre total de comparaisons est essentielle.