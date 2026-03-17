philosophers/
├── includes/
│   └── philosophers.h
├── srcs/
│   ├── main.c
│   ├── init.c
│   ├── parsing.c
│   ├── routine.c
│   ├── actions.c
│   ├── monitor.c
│   └── utils.c
├── Makefile

void	*philo_routine(void *arg)
{
    // 1. Décalage pour les philos pairs (évite deadlock)
    // 2. Boucle :
    //    - take_forks()
    //    - eat()
    //    - drop_forks()
    //    - sleep()
    //    - think()
    // 3. Vérifier is_dead à chaque itération
}

Étape 5 — Monitor (thread surveillant)
Thread séparé qui vérifie en continu :
Si un philo n'a pas mangé depuis time_to_die ms → mort
Si tous les philos ont mangé nb_meals fois → fin
Utiliser death_mutex pour éviter les data races

Étape 6 — Fonctions utilitaires
Fonction	Rôle
get_time()	Retourne le temps en ms (gettimeofday)
ft_usleep()	Sleep précis avec boucle active
print_action()	Affiche avec print_mutex
⚠️ Points critiques à ne pas rater
Aucun data race → valgrind --tool=helgrind
Aucun deadlock → ordre de prise des fourchettes
ft_usleep précis → usleep seul n'est pas assez précis
Un seul philo → cas particulier à gérer
Protéger tous les accès à is_dead et last_meal_time


test :

./philo 1 800 200 200        # doit mourir
./philo 5 800 200 200        # ne doit pas mourir
./philo 5 800 200 200 7      # doit s'arrêter après 7 repas
./philo 4 410 200 200        # ne doit pas mourir
./philo 4 310 200 100        # doit mourir