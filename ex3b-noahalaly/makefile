FLAGS = -Wall -Wextra -Wvla -std=c99

.PHONY:
all: tweets snake

.PHONY:
clean:
	rm -f *.o tweets_generator snakes_and_ladders

linked_list.o: linked_list.c linked_list.h
	gcc $(FLAGS) -c linked_list.c

markov_chain.o: markov_chain.c markov_chain.h linked_list.h
	gcc $(FLAGS) -c markov_chain.c

tweets_generator.o: tweets_generator.c markov_chain.h linked_list.h
	gcc $(FLAGS) -c tweets_generator.c

snakes_and_ladders.o: snakes_and_ladders.c markov_chain.h linked_list.h
	gcc $(FLAGS) -c snakes_and_ladders.c

tweets: tweets_generator.o markov_chain.o linked_list.o
	gcc tweets_generator.o markov_chain.o linked_list.o -o tweets_generator

snake: snakes_and_ladders.o markov_chain.o linked_list.o
	gcc snakes_and_ladders.o markov_chain.o linked_list.o -o snakes_and_ladders