CC=gcc
CFLAGS=-Wall -Wextra -fPIC
INCLUDE_DIR = .
SRCS = xml.c xml_print.c xml_utils.c
OBJS = $(SRCS:.c=.o)
TARGET = libxml.so

all: $(TARGET)	

$(TARGET):$(OBJS)
	$(CC) $^ -shared -o $(TARGET)

%.o:%.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $^ -o $@

install: $(TARGET)
	install -d libxml
	install -d libxml/include
	install -d libxml/lib
	install -m 644 $^ libxml/lib
	install -m 644 $(INCLUDE_DIR)/*.h libxml/include

clean:
	rm -f *.o $(TARGET)