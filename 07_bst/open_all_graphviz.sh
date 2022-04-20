rm -f /tmp/graphviz*.dot.png; ls -1 *.dot | xargs -I{} dot {} -T png -o /tmp/graphviz_{}.png; feh /tmp/graphviz*.dot.png
