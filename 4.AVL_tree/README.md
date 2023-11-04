# AVL strom

Vaším úkolem je implementovat šablonu třídy Tree parametrizovanou typem ukládaných prvků T. Tato třída by měla udržovat prvky ve struktuře AVL stromu dle uspořádání std::less<T> (či operátoru <). Vyžadované metody jsou:

```cpp
• size(): Vrátí počet prvků ve stromu.
• find(t): Nalezne prvek t ve stromu a vrátí na něj const ukazatel, nebo • nullptr, pokud prvek ve stromu není.
• insert(t): Pokusí se vložit t. Vrátí, zda se vložení povedlo. Vložení selže, pokud strom již prvek se stejnou hodnotou obsahuje.
• erase(t): Smaže prvek t, pokud je t ve stromě. Vrací, zda byl prvek smazán.
```

Kopírování ani přesouvání objektů typu Tree není testováno. Pro účely testování je třeba implementovat následující statické metody třídy `Tree::TesterInterface`:
```cpp
• root(tree): Vrátí pointer na kořen stromu. (Na uzel, nikoliv na hodnotu v něm uloženou.)
• parent(n): Vrátí pointer na otce uzlu n. Pro kořen vrátí nullptr. Pokud vaše implementace nemá ukazatele na otce a máte nastaveno config::PARENT_POINTERS na false, můžete metodu smazat nebo vždy vracet nullptr.
• right(n): Vrátí pointer na pravého syna n nebo nullptr, pokud neexistuje.
• left(n): Vrátí pointer na levého syna n nebo nullptr, pokud neexistuje.
• value(n): Vrátí const referenci na hodnotu uloženou v uzlu n.
```
Pro snazší vývoj jsou v šabloně k dispozici následující konfigurační volby:

```cpp
• config::CHECK_DEPTH: Pokud je true, zapne kontrolu tvaru AVL stromu, jinak je pouze kontrolováno, že strom je korektní binární vyhledávácí. Progtest tuto volbu ignoruje. Defaultně false, zapněte až implementujete vyvažování.
• config::PARENT_POINTERS: Určuje, zda se mají testovat i ukazatele na otce. Progtest tuto volbu respektuje za cenu drobné bodové ztráty, pokud ukazatele na otce nebudou implementovány. Defaultně true.
```