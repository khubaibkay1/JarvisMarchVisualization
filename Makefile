CXXFLAGS = -g -Wall #-march=native -fopenmp -O2 -fno-omit-frame-pointer -flto -Wno-sign-compare #-fsanitize=address
CAIROFLAGS = `pkg-config --cflags --libs cairo`
OBJS = main.o helper.o 
main: $(OBJS)
	gcc $(CXXFLAGS) -o $@ $(OBJS) $(CAIROFLAGS)

helper.o: helper.c
	gcc $(CXXFLAGS) $(CAIROFLAGS) helper.c -c -o helper.o

main.o: main.c
	gcc $(CXXFLAGS) -c -o $@ $(CAIROFLAGS) main.c

clean:
	rm -f helper.o main.o main
	rm -f images/* main.mp4

run: main
	rm -f images/*
	./main
	rm -f main.mp4
	ffmpeg -start_number 0 -framerate 30 -i ./images/image%5d.png -b 5000k -r 60 -vcodec mpeg4 main.mp4