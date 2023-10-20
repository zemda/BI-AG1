# Binární halda I

Vaším úkolem je implementovat šablonu třídy template < typename T, typename Comp > struct BinaryHeap, která představuje binární haldu s prvky typu T setřízenou dle komparátoru Comp uloženou v poli. Jak je v C++ zvykem, comp(a, b) == true znamená, že a je ostře menší než b. Požadované metody jsou:

- Defaultní konstruktor a konstruktor s parametrem typu Comp. Defaultní konstruktor by měl vytvořit komparátor jeho defaultním konstruktorem.
- empty(): Zjistí, zda je halda prázdná.
- size(): Vrátí počet prvků v haldě.
- min(): Vrátí současné minimum. Vyvolá výjimku std::out_of_range, pokud je halda prázdná.
- extract_min(): Vrátí minimum a současně ho odstraní z haldy. Vyvolá výjimku std::out_of_range, pokud je halda prázdná. Musí vracet totéž minimum jako metoda min().
- push(t): Vloží prvek t do haldy. Je vhodné brát argument hodnotou a přesouvat ho pomocí std::move.

Dále musí šablona BinaryHeap obsahovat strukturu TestHelper, která umožní testování struktury haldy. TestHelper musí obsahovat následující statické metody:
- index_to_value(H, i): Vrátí referenci na i-tý prvek v haldě H.
- root_index(): Index kořene haldy.
- parent(i): Index otce prvku na pozici i.
- child(p, i): Index i-tého (tj. nultého nebo prvního) syna uzlu na pozici p.

Můžete předpokládat, že T má defaultní konstruktor a move konstruktor i operátor přiřazení. Naopak T nemusí být kopírovatelné. Objekty třídy BinaryHeap nejsou v testech přesouvány ani kopírovány.