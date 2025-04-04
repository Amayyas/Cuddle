# Cuddle

Cuddle est une bibliothèque C légère et performante pour la manipulation de données tabulaires, inspirée par pandas en Python. Elle permet de charger, traiter et analyser des données structurées facilement dans vos applications C.

## Fonctionnalités

- **Lecture/Écriture CSV** : Chargement et sauvegarde de fichiers CSV
- **Manipulation de données** :
  - Filtrage de données (`df_filter`)
  - Tri (`df_sort`) 
  - Sélection de sous-ensembles (`df_head`, `df_tail`)
  - Application de fonctions (`df_apply`)
  - Regroupement et agrégation (`df_groupby`)
- **Conversion de types** : Conversion entre différents types de données (int, float, string, etc.)
- **Statistiques descriptives** : Calcul des métriques de base (moyenne, écart-type, min/max)
- **Affichage et exploration** : Affichage des dimensions (`df_shape`), informations sur les colonnes (`df_info`)

## Installation

```bash
git clone git@github.com:Amayyas/Cuddle.git
cd Cuddle
make
```

La compilation produira une bibliothèque statique `libcuddle.a` que vous pourrez lier à vos projets.

## Utilisation

### Exemple basique

```c
#include "dataframe.h"
#include <stdio.h>

int main() {
    // Charger un fichier CSV
    dataframe_t *df = df_read_csv("data.csv", ",");
    
    // Afficher les informations sur le dataframe
    printf("Dimensions: %d lignes, %d colonnes\n", df->nb_rows, df->nb_columns);
    
    // Afficher les informations sur les colonnes
    df_info(df);
    
    // Obtenir les 5 premières lignes
    dataframe_t *head = df_head(df, 5);
    df_print_csv(head);
    
    // Libérer la mémoire
    df_free(head);
    df_free(df);
    
    return 0;
}
```

## Fonctions principales

### Lecture/Écriture

```c
dataframe_t *df_read_csv(const char *filename, const char *separator);
int df_write_csv(const dataframe_t *dataframe, const char *filename);
void df_print_csv(const dataframe_t *dataframe);
```

### Exploration de données

```c
void df_info(dataframe_t *dataframe);
void df_describe(dataframe_t *dataframe);
dataframe_shape_t df_shape(dataframe_t *dataframe);
```

### Sous-ensembles

```c
dataframe_t *df_head(dataframe_t *dataframe, int nb_rows);
dataframe_t *df_tail(dataframe_t *dataframe, int nb_rows);
```

### Filtrage

```c
dataframe_t *df_filter(dataframe_t *dataframe, const char *column, 
                       bool (*filter_func)(void *value));
```

### Tri

```c
dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
                    bool (*sort_func)(void *value1, void *value2));
```

### Transformation

```c
dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
                     void *(*apply_func)(void *value));
                     
dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
                       column_type_t downcast);
```

### Groupement

```c
dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
                       const char **to_aggregate,
                       void *(*agg_func)(void **values, int nb_values));
```

## Types de données supportés

- `BOOL` : Valeurs booléennes
- `INT` : Entiers signés
- `UINT` : Entiers non signés
- `FLOAT` : Nombres à virgule flottante
- `STRING` : Chaînes de caractères

## Libération de la mémoire

Cuddle gère l'allocation dynamique de mémoire, donc n'oubliez pas de libérer les ressources quand vous avez terminé :

```c
void df_free(dataframe_t *dataframe);
```

## Compilation et tests

Le projet inclut un Makefile pour faciliter la compilation:

- `make` : Compile la bibliothèque
- `make clean` : Supprime les fichiers objets
- `make fclean` : Supprime les fichiers objets et la bibliothèque
- `make re` : Effectue une recompilation complète
- `make test` : Compile et exécute les tests avec valgrind
- `make direct_test` : Compile et exécute les tests sans valgrind
