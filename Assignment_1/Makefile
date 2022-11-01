CC = gcc
DBUG = -g
CCFLAGS = -O2 -Wall -pedantic
OBJFILES_DH = utils.o dh_assign_1.o main_dh.o
OBJFILES_RSA = utils.o rsa_assign_1.o main_rsa.o
TARGET_DH = dh_assign_1
TARGET_RSA = rsa_assign_1

all: $(TARGET_DH) $(TARGET_RSA)
dh: $(TARGET_DH)
rsa: $(TARGET_RSA)

$(TARGET_DH): $(OBJFILES_DH)
	$(CC) $(CFLAGS) $(DBG) -o $(TARGET_DH) $(OBJFILES_DH) -lgmp

$(TARGET_RSA): $(OBJFILES_RSA)
	$(CC) $(CFLAGS) $(DBG) -o $(TARGET_RSA) $(OBJFILES_RSA) -lgmp

clean_dh:
	rm -f $(TARGET_DH) dh_assign_1.o main_dh.o

clean_rsa:
	rm -f $(TARGET_RSA) rsa_assign_1.o main_rsa.o

clean:
	rm -f $(TARGET_DH) $(TARGET_RSA) *.o