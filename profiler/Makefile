test: profiler.o test_profiler.o
	$(CC) $(CFLAGS) $^ -o $@

profiler.o: profiler.c
	$(CC) $(CFLAGS) -c $^ -o $@

test_profiler.o: test_profiler.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm *.o test_profiler

.PHONY: clean
