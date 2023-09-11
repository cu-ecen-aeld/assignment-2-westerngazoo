# native compiler
CC := gcc

# if cross compiling, set CROSS_COMPILE to the prefix of the cross compiler
CROSS_COMPILE ?=

# Opciones de compilación
CFLAGS := -Wall -Wextra

# Nombre del archivo binario
TARGET := writer

# source files
SRCS := writer.c

# Generar nombres de archivos objeto
OBJS := $(SRCS:.c=.o)

# Target 
default: $(TARGET)

#libs to be linked
LIBS := -lm

#headers to include libgen
CFLAGS += -I/usr/include # for dirname() and basename()

# Compile and link
$(TARGET): $(OBJS)
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $(LIBS) -o $@ $^

# rules for object files
%.o: %.c
	$(CROSS_COMPILE)$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Clean target
clean:
	rm -f $(TARGET) $(OBJS)
