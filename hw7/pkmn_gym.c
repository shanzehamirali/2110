/**
 * @file pkmn_gym.c
 * @author Shanzeh Amirali
 *
 * @date 2024-03-xx
 */

// DO NOT MODIFY THE INCLUDE(S) LIST
#include "pkmn_gym.h"

// DO NOT MODIFY THE GLOBAL VARIABLE(S) LIST
struct Gym gym;

// ALWAYS check the validity of the passed in arguments
// (i.e. not NULL, in the correct range, not too long)

// If any of the parameters are invalid, the function should
// do nothing and return FAILURE.



/** register_trainer
 * @brief Add a new trainer to the gym with the provided parameters.
 * @param name the name of the trainer
 * @return FAILURE if parameters invalid or the gym is full, SUCCESS otherwise
*/
int register_trainer(const char *name) {
    if (name == NULL || my_strlen(name) >= MAX_NAME_LENGTH) {
        return FAILURE;
    }
    if (gym.num_trainers == MAX_TRAINER_LENGTH) {
        return FAILURE;
    }
    my_strncpy(gym.trainers[gym.num_trainers].name, name, MAX_NAME_LENGTH);
    gym.trainers[gym.num_trainers].party_size = 0;
    gym.trainers[gym.num_trainers].num_wins = 0;
    gym.num_trainers++;
    return SUCCESS;
}

/** unregister_trainer
 * @brief Removes a trainer from the gym.
 * @param name the name of the trainer
 * @return FAILURE if parameters invalid or the trainer is not found, SUCCESS otherwise
*/
int unregister_trainer(const char *name) {
    if (name == NULL || my_strlen(name) >= MAX_NAME_LENGTH) {
            return FAILURE;
        }
    for (int i = 0; i < gym.num_trainers; i++) {
        if (my_strncmp(gym.trainers[i].name, name, MAX_NAME_LENGTH) == 0) {
            for (int j = i; j < gym.num_trainers; j++) {
                gym.trainers[j] = gym.trainers[j + 1];
            }
            gym.num_trainers--;
            return SUCCESS;
        }
    }
    return FAILURE;
}

/** catch_pokemon
 * @brief Creates a new Pokémon and adds it to
 * the trainer's party.
 * @param trainer pointer to the trainer who caught this Pokémon
 * @param species the species of the Pokémon caught
 * @param level the level of the Pokémon caught
 * @return FAILURE if parameters invalid or the trainer's party is full, SUCCESS otherwise
*/
int catch_pokemon(struct Trainer *trainer, const char *species, int level) {
    if (trainer == NULL || species == NULL || level < 1 || level > 100 || my_strlen(species) >= MAX_NAME_LENGTH) {
        return FAILURE;
    }
    if (trainer->party_size >= MAX_PARTY_LENGTH) {
        return FAILURE;
    }
    struct Pokemon poke;
    my_strncpy(poke.species, species, MAX_NAME_LENGTH);
    poke.level = level;
    trainer->party[trainer->party_size] = poke;
    trainer->party_size += 1;
    return SUCCESS;
}

/** release_pokemon
 * @brief Removes a Pokémon from a trainer's party.
 * @param trainer pointer to the trainer who is releasing a Pokémon
 * @param species the species of the Pokémon to release
 * @return FAILURE if parameters invalid or the Pokémon is not found in the trainer's party, SUCCESS otherwise
*/
int release_pokemon(struct Trainer *trainer, const char *species) {
    if (trainer == NULL || species == NULL || my_strlen(species) >= MAX_NAME_LENGTH) {
        return FAILURE;
    }
    for (int i = 0; i < (trainer->party_size); i++) {
        if (my_strncmp(trainer->party[i].species, species, MAX_NAME_LENGTH) == 0) {
            for (int j = i; j < trainer->party_size; j++) {
                trainer->party[j] = trainer->party[j + 1];
            }
            trainer->party_size--;
            return SUCCESS;
        }
    }
    return FAILURE;
}

/** count_species
 * @brief Count the total number of Pokémon of a given species
 * out of the parties of every trainer in this gym.
 * @param species the name of the species to search for
 * @return FAILURE if parameters invalid, otherwise the number of Pokémon in the gym of the given species
*/
int count_species(const char *species) {
    if (species == NULL || my_strlen(species) >= MAX_NAME_LENGTH) {
        return FAILURE;
    }
    int count = 0;
    for (int i = 0; i < gym.num_trainers; i++) {
        for (int j = 0; j < gym.trainers[i].party_size; j++) {
            if (my_strncmp(species, gym.trainers[i].party[j].species, MAX_NAME_LENGTH) == 0) {
                count++;
            }
        }
    }
    return count;
}

/** trade_pokemon
 * @brief Trade two Pokémon between two trainers,
 * swapping their positions in their parties.
 * @param t0 pointer to the first trainer in the trade
 * @param party_index_0 the index of the Pokémon to trade in the first trainer's party
 * @param t1 pointer to the second trainer in the trade
 * @param party_index_1 the index of the Pokémon to trade in the second trainer's party
 * @return FAILURE if 
 *                  parameters invalid,
 *                  both Trainers are the same,
 *                  party_index_0 or party_index_1 do not point to pokemon,
 *         SUCCESS otherwise
*/
int trade_pokemon(struct Trainer *t0, int party_index_0, struct Trainer *t1, int party_index_1) {
    if (t0 == NULL || t1 == NULL) {
        return FAILURE;
    }
    if (t0 == t1) {
        return FAILURE;
    }
    if (party_index_0 < 0 || party_index_0 >= t0->party_size || party_index_1 < 0 || party_index_1 >= t1->party_size) {
        return FAILURE;
    }
    struct Pokemon temp = t0->party[party_index_0];
    t0->party[party_index_0] = t1->party[party_index_1];
    t1->party[party_index_1] = temp;
    return SUCCESS;
}

/** battle_trainer
 * @brief Start a battle between two trainers.
 * 
 * The num_wins variable of the winner of this battle should
 * also be incremented to reflect the trainer's win.
 * 
 * @param challenger pointer to the trainer who initiated the battle
 * @param opponent pointer to the trainer who was initiated by the challenger
 * @return FAILURE if parameters invalid, 0 if the challenger wins, 1 if the opponent wins
*/
int battle_trainer(struct Trainer *challenger, struct Trainer *opponent) {
    if (challenger == NULL || opponent == NULL) {
        return FAILURE;
    }
    int c_wins = 0;
    int o_wins = 0;
    int matches = 0;
    if (challenger->party_size >= opponent->party_size) {
        c_wins += (challenger->party_size - opponent->party_size);
        matches = opponent->party_size;
    } else if (challenger->party_size < opponent->party_size) {
        o_wins += (opponent->party_size - challenger->party_size);
        matches = challenger->party_size;
    }
    for (int i = 0; i < matches; i++) {
        if (challenger->party[i].level > opponent->party[i].level) {
            c_wins++;
        } else if (challenger->party[i].level < opponent->party[i].level) {
            o_wins++;
        }
    }
    if (o_wins >= c_wins) {
        opponent->num_wins++;
        return 1;
    } else {
        challenger->num_wins++;
        return 0;
    }
}

/** find_champion
 * @brief Find the CHAMPION!!! (i.e., the trainer in this gym with the most wins.)
 * If several trainers have the maximum number of wins, pick the first in the gym trainer array with
 *  the maximum wins.
 * @return a pointer to the Trainer with the most wins, NULL is the gym has no Trainers in it
*/
struct Trainer *find_champion(void) {
    if (gym.num_trainers == 0) {
        return NULL;
    }
    int max = 0;
    struct Trainer *winner = &gym.trainers[0];
    for (int i = 0; i < gym.num_trainers; i++) {
        if (gym.trainers[i].num_wins > max) {
            max = gym.trainers[i].num_wins;
            winner = &gym.trainers[i];
        }
    }
    return winner;
}