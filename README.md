# philosophers

Two solutions to the problem of [dining philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem).  
-In the first case philosophers are threads and forks are in between them.  
-In the second case philosophers are processes and forks are in the middle of the table.  

Task definition: [subject](https://drive.google.com/file/d/1ivrehSAzw_d76PPCLjt_v5CNfAkqW-tK/view?usp=sharing)

This project is written according to the [Norm](https://drive.google.com/file/d/1cf_thz7IUjWxVRlPbDyfv0hACNSz9_9s/view?usp=sharing).

### Short instructions:
1. Type "make" in one of two directories
2. Execute ./philo 'num_of_philos' 'time_to_die' 'time_to_eat' 'time_to_sleep' ['num_of_meals']  
* **'num_of_philos'** is the number of philosophers and the number of forks  
* **'time_to_die'** ms is the time in which the philosopher will die if he does not eat  
* **'time_to_eat'** ms is the time it takes for a philosopher to eat  
* **'time_to_sleep'** ms is the time it takes for a philosopher to sleep after eating  
* **'num_of_meals'** [optional] is the number of meals to get one philosopher full;  
  once all the philosophers are full, the simulation stops
