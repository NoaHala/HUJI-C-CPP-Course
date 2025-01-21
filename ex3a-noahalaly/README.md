noahalaly

fix: files that were accidentally submitted have been removed
tweet_generator.c line16: malloc size is "str_len + 1" instead of "str_len"
tweet_generator.c line67: "strdup" got replaced by "str_alloc"
markov_chain.c line267: deleted the line