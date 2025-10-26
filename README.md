# C tua
## Reppositori de 'na conferenza 'n romanesco che ho dato pe' er GDG de Roma

Er 25 ottobbre der 2025 ho dato 'na chiacchiera ar Giddiggì Roma DevFest, indove ho parlato der linguaggio C, de quanto è fico, der perché lo dovemo ancora programma' e, a'a fine, de quanto me piace.

Drento 'sto reppositori lascio er codice che ho scritto pe' ffa' 'n'esempio de comme se po' ffa' programmazzione a oggetti in C, de comme se ponno gesti' l'eccezzioni, li moduli e tutti l'artri mmortacci loro da'a programmazzione moderna.

Ce sta 'na libbreria pe' ggesti' 'na pila ('no stacche come dicheno quelli bbravi) de robba quarziasi, in pratica de ppuntatori a vvoide, che esporta 'na classe `Pila` e quarche metodo de bbase. A cosa fica è che drento 'na pila ce poi ficca' quello chette pare, nummeri, stringhe, (puntatori a) funzzioni, artre pile e l'anima de li mortacci tua. Er nummero de oggetti che che poi spigne drento è arbitrario, perché, internamente, l'oggetto creato dar costruttore se espanne si e quanno serve. Pero' 'o devi costruì e distrugge espricitamente, coi metodi `ppila_daje`e `pila_levetedarcazzo`. Ce sta un filetto de prova co' un `main` pe' mostrà come se usa 'sta classe.

Ppoi faccio puro vede' comme a classe Pila se po' usa' pe' imprementa' 'na semprice carcolatrice, che usa usa 'du pile, una pe' contene' 'li valori temporanei e n'antra pe' contene' un codice che rappresenta in forma postefissa (mica cazzo) l'opperazzioni da fa' pe' carcola' l'espressione. Aho, er parsere è fatto ca'a tecnica bottome-uppe co' preccedenza d'o'opperatori, mica na fregnacca quarziasi. Puro questa è imprementata come 'na classe, cosicché poi alloca' quanti cazzo de carcoli te pare e falli in modo indipennente l'uni dall'artri.

Lascio puro 'e slidde in piddieffe, i luccidi comme se chiammavano a 'li tempi mia.

Vabbe', si ve piace bene, si no sticazzi.
