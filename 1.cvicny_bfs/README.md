# BFS
Vaším úkolem je implementovat funkci `size_t bfs(const Graph& G, Vertex u, std::vector<Vertex>& P, std::vector<size_t>& D)`, která implementuje prohledávání do šířky. Argumenty jsou:

- Graph G: Graf, který máte prohledávat. Popis třídy Graph je níže.
- Vertex u: Vrchol, ze kterého prohledávání začíná.
- `std::vector<Vertex>& P`: Pole předchůdců. Před zavoláním funkce bfs je vždy inicializováno na správnou velikost a vyplněno konstantou `NO_VERTEX`.
- `std::vector<size_t>& D`: Pole vzdáleností. Před zavoláním funkce bfs je vždy inicializováno na správnou velikost a vyplněno konstantou `NO_DISTANCE`.

Návratovou hodnotou je počet navštívených vrcholů a dále musí být správně vyplněna pole P a D. Předchůdce počátečního vrcholu nastavte na konstantu ROOT. Vaše implementace by měla být lineární ve velikosti navštívené části grafu.

Třída Graph představuje neorientovaný nebo orientovaný graf. Důležité metody jsou:
- `vertices()`: Počet vrcholů.
- `operator[](Vertex v)`: Seznam sousedů (resp. následníků) vrcholu v. Vrcholy jsou celá čísla od 0.
- Metody `begin()` a `end()`, které umožňují iteraci přes vrcholy a použití třídy Graph v range-for cyklu takto for (Vertex v : G) ....

Časové limity jsou 5 sekund na malý test a 3.5 sekundy na velký.