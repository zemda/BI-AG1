# TopSort

Vaším úkolem je implementovat funkci `std::pair<bool, std::vector<Vertex>> topsort(const Graph& G)`. Návratovou hodnotou je buď:

- true a seznam všech vrcholů v topologickém uspořádání, nebo
- false a seznam vrcholů, které tvoří kružnici (z posledního do prvního vrcholu seznamu také musí vést hrana).

Třída Graph představuje orientovaný graf. Důležité metody jsou:
- `vertices()`: Počet vrcholů.
- `operator[](Vertex v)`: Seznam sousedů vrcholu v. Vrcholy jsou celá čísla od 0.
- Metody `begin()` a `end()`, které umožňují iteraci přes vrcholy a použití třídy `Graph` v range-for cyklu takto `for (Vertex v : G)` ....
- `reversed()`: Vrátí nový graf vzniklý otočením orientace všech hran.

Časové limity jsou 5 sekund na malý test a 3 sekundy na velký.