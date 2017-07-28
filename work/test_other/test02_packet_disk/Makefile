all:
	gcc -o receiver receiver.c
	gcc -o sender sender.c

exec:
	./receiver

exec_tmpfs:
	rmdir tmpfs_space
	mkdir tmpfs_space
	sudo mount -t tmpfs -o size=256m tmpfs_space ./tmpfs_space
	./receiver
	sudo umount tmpfs_space
