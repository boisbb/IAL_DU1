
/* c206.c **********************************************************}
{* Téma: Dvousměrně vázaný lineární seznam
**
**                   Návrh a referenční implementace: Bohuslav Křena, říjen 2001
**                            Přepracované do jazyka C: Martin Tuček, říjen 2004
**                                            Úpravy: Kamil Jeřábek, září 2019
**
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int.
** Seznam bude jako datová abstrakce reprezentován proměnnou
** typu tDLList (DL znamená Double-Linked a slouží pro odlišení
** jmen konstant, typů a funkcí od jmen u jednosměrně vázaného lineárního
** seznamu). Definici konstant a typů naleznete v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu
** s výše uvedenou datovou částí abstrakce tvoří abstraktní datový typ
** obousměrně vázaný lineární seznam:
**
**      DLInitList ...... inicializace seznamu před prvním použitím,
**      DLDisposeList ... zrušení všech prvků seznamu,
**      DLInsertFirst ... vložení prvku na začátek seznamu,
**      DLInsertLast .... vložení prvku na konec seznamu,
**      DLFirst ......... nastavení aktivity na první prvek,
**      DLLast .......... nastavení aktivity na poslední prvek,
**      DLCopyFirst ..... vrací hodnotu prvního prvku,
**      DLCopyLast ...... vrací hodnotu posledního prvku,
**      DLDeleteFirst ... zruší první prvek seznamu,
**      DLDeleteLast .... zruší poslední prvek seznamu,
**      DLPostDelete .... ruší prvek za aktivním prvkem,
**      DLPreDelete ..... ruší prvek před aktivním prvkem,
**      DLPostInsert .... vloží nový prvek za aktivní prvek seznamu,
**      DLPreInsert ..... vloží nový prvek před aktivní prvek seznamu,
**      DLCopy .......... vrací hodnotu aktivního prvku,
**      DLActualize ..... přepíše obsah aktivního prvku novou hodnotou,
**      DLSucc .......... posune aktivitu na další prvek seznamu,
**      DLPred .......... posune aktivitu na předchozí prvek seznamu,
**      DLActive ........ zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce
** explicitně uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako
** procedury (v jazyce C procedurám odpovídají funkce vracející typ void).
**/

#include "c206.h"

int solved;
int errflg;

void DLError() {
/*
** Vytiskne upozornění na to, že došlo k chybě.
** Tato funkce bude volána z některých dále implementovaných operací.
**/
    printf ("*ERROR* The program has performed an illegal operation.\n");
    errflg = TRUE;             /* globální proměnná -- příznak ošetření chyby */
    return;
}

void DLInitList (tDLList *L) {
/*
** Provede inicializaci seznamu L před jeho prvním použitím (tzn. žádná
** z následujících funkcí nebude volána nad neinicializovaným seznamem).
** Tato inicializace se nikdy nebude provádět nad již inicializovaným
** seznamem, a proto tuto možnost neošetřujte. Vždy předpokládejte,
** že neinicializované proměnné mají nedefinovanou hodnotu.
**/

  L = malloc(sizeof(tDLList));
  if (L == NULL)
    DLError();
  L->First = NULL;
  L->Act = NULL;
  L->Last = NULL;

 ////solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDisposeList (tDLList *L) {
/*
** Zruší všechny prvky seznamu L a uvede seznam do stavu, v jakém
** se nacházel po inicializaci. Rušené prvky seznamu budou korektně
** uvolněny voláním operace free.
**/

  struct tDLElem *tmp = L->First;
  struct tDLElem *temp;
  while(tmp != NULL){
    temp = tmp->rptr;
    free(tmp);
    tmp = temp;
  }
  L->First = NULL;
  L->Act = NULL;
  L->Last = NULL;

 ////solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertFirst (tDLList *L, int val) {
/*
** Vloží nový prvek na začátek seznamu L.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

  if (L->First == NULL) {
    L->First = malloc(sizeof(struct tDLElem));
    if (L->First == NULL) {
      DLError();
    }
    L->First->data = val;
    L->First->lptr = NULL;
    L->First->rptr = NULL;
    L->Last = L->First;
  }
  else {
    L->First->lptr = malloc(sizeof(struct tDLElem));
    if (L->First->lptr == NULL)
      DLError();
    L->First->lptr->data = val;
    L->First->lptr->lptr = NULL;
    L->First->lptr->rptr = L->First;
    L->First = L->First->lptr;
  }

 ////solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLInsertLast(tDLList *L, int val) {
/*
** Vloží nový prvek na konec seznamu L (symetrická operace k DLInsertFirst).
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

  if (L->First == NULL){
    L->Last = malloc(sizeof(struct tDLElem));
    L->Last->data = val;
    L->Last->lptr = NULL;
    L->Last->rptr = NULL;
    L->First = L->Last;
    return;
  }

  L->Last->rptr = malloc(sizeof(struct tDLElem));
  if (L->Last->rptr == NULL)
    DLError();
  L->Last->rptr->data = val;
  L->Last->rptr->lptr = L->Last;
  L->Last = L->Last->rptr;
  L->Last->rptr = NULL;
  //printf("%d\n", L->Last->data);

 ////solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLFirst (tDLList *L) {
/*
** Nastaví aktivitu na první prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

  L->Act = L->First;

 ////solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLLast (tDLList *L) {
/*
** Nastaví aktivitu na poslední prvek seznamu L.
** Funkci implementujte jako jediný příkaz (nepočítáme-li return),
** aniž byste testovali, zda je seznam L prázdný.
**/

  L->Act = L->Last;

 ////solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyFirst (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu prvního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

if (L->First == NULL)
  DLError();
else
  *val = L->First->data;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopyLast (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu posledního prvku seznamu L.
** Pokud je seznam L prázdný, volá funkci DLError().
**/

  if (L->First == NULL)
    DLError();
  else
    *val = L->Last->data;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteFirst (tDLList *L) {
/*
** Zruší první prvek seznamu L. Pokud byl první prvek aktivní, aktivita
** se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/

  if (L->First == NULL)
    return;
  if (L->First->rptr == NULL){
    L->First = NULL;
    L->Last = NULL;
    L->Act = NULL;
    return;
  }

  if(L->First == L->Act)
    L->Act = NULL;

  struct tDLElem *temp = L->First->rptr;
  free(L->First);
  L->First = temp;
  L->First->lptr = NULL;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLDeleteLast (tDLList *L) {
/*
** Zruší poslední prvek seznamu L. Pokud byl poslední prvek aktivní,
** aktivita seznamu se ztrácí. Pokud byl seznam L prázdný, nic se neděje.
**/

  if (L->Last == NULL)
    return;

  if (L->Last->lptr == NULL){
    L->Last = NULL;
    L->First = NULL;
    L->Act = NULL;
    return;
  }

  if(L->Last == L->Act)
    L->Act = NULL;

  struct tDLElem *temp = L->Last->lptr;
  free(L->Last);
  L->Last = temp;
  L->Last->rptr = NULL;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostDelete (tDLList *L) {
/*
** Zruší prvek seznamu L za aktivním prvkem.
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** posledním prvkem seznamu, nic se neděje.
**/

// If L->Act->rptr == NULL, it means that L->Act == L->Last
  if (L->Act == NULL || L->Act->rptr == NULL)
		return;
  struct tDLElem *temp = L->Act->rptr->rptr;
  free(L->Act->rptr);
  L->Act->rptr = temp;
  if(L->Act->rptr == NULL)
    L->Last = L->Act;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreDelete (tDLList *L) {
/*
** Zruší prvek před aktivním prvkem seznamu L .
** Pokud je seznam L neaktivní nebo pokud je aktivní prvek
** prvním prvkem seznamu, nic se neděje.
**/

  if (L->Act == NULL || L->Act->lptr == NULL)
    return;
  struct tDLElem *temp = L->Act->lptr->lptr;
  free(L->Act->lptr);
  L->Act->lptr = temp;
  if(L->Act->lptr == NULL)
    L->First = L->Act;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPostInsert (tDLList *L, int val) {
/*
** Vloží prvek za aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

  struct tDLElem *tmp = NULL;

  if (L->Act == NULL)
    return;

  if (L->Act->rptr == NULL){
    L->Act->rptr = malloc(sizeof(struct tDLElem));
    if (L->Act->rptr == NULL)
      DLError();
    else{
      L->Act->rptr->lptr = L->Act;
      L->Act->rptr->data = val;
      L->Act->rptr->rptr = NULL;
      L->Last = L->Act->rptr;
    }
  }
  else {
    tmp = malloc(sizeof(struct tDLElem));
    if (tmp == NULL)
      DLError();
    else {
      tmp->data = val;
      tmp->rptr = L->Act->rptr;
      tmp->lptr = L->Act;
    }
  }

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLPreInsert (tDLList *L, int val) {
/*
** Vloží prvek před aktivní prvek seznamu L.
** Pokud nebyl seznam L aktivní, nic se neděje.
** V případě, že není dostatek paměti pro nový prvek při operaci malloc,
** volá funkci DLError().
**/

  if (L->Act == NULL)
    return;

  if(L->Act->lptr == NULL){
    L->Act->lptr = malloc(sizeof(struct tDLElem));
    if (L->Act->lptr == NULL)
      DLError();
    else{
      L->Act->lptr->rptr = L->Act;
      L->Act->lptr->data = val;
      L->Act->lptr->lptr = NULL;
      L->First = L->Act->lptr;
    }
  }
  else {
    struct tDLElem *tmp  = malloc(sizeof(struct tDLElem));
    if (tmp == NULL)
      DLError();
    else {
      tmp->data = val;
      tmp->lptr = L->Act->lptr;
      tmp->rptr = L->Act;
    }
  }
 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLCopy (tDLList *L, int *val) {
/*
** Prostřednictvím parametru val vrátí hodnotu aktivního prvku seznamu L.
** Pokud seznam L není aktivní, volá funkci DLError ().
**/

  if (L->Act == NULL)
    DLError();
  else
    *val = L->Act->data;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLActualize (tDLList *L, int val) {
/*
** Přepíše obsah aktivního prvku seznamu L.
** Pokud seznam L není aktivní, nedělá nic.
**/

  if (L->Act == NULL)
    return;
  L->Act->data = val;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

void DLSucc (tDLList *L) {
/*
** Posune aktivitu na následující prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
**/

  if (L->Act == NULL)
    return;
  L->Act = L->Act->rptr;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}


void DLPred (tDLList *L) {
/*
** Posune aktivitu na předchozí prvek seznamu L.
** Není-li seznam aktivní, nedělá nic.
** Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
**/

  //printf("%d\n", L->Act->lptr->data);
  if (L->Act == NULL)
    return;
  L->Act = L->Act->lptr;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

int DLActive (tDLList *L) {
/*
** Je-li seznam L aktivní, vrací nenulovou hodnotu, jinak vrací 0.
** Funkci je vhodné implementovat jedním příkazem return.
**/

  return (L->Act == NULL) ? 0 : 1;

 //solved = FALSE;                   /* V případě řešení, smažte tento řádek! */
}

/* Konec c206.c*/
