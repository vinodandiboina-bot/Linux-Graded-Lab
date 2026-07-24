#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "employees.dat"

typedef struct {
    int  id;
    char name[40];
    char role[20];
} Employee;

void write_record(int fd, Employee *emp) {
    write(fd, emp, sizeof(Employee));
}

void read_record(int fd, int index, Employee *emp) {
    lseek(fd, index * sizeof(Employee), SEEK_SET);
    read(fd, emp, sizeof(Employee));
}

void update_record(int fd, int index, Employee *updated) {
    lseek(fd, index * sizeof(Employee), SEEK_SET);
    write(fd, updated, sizeof(Employee));
}

int main() {
    int fd = open(FILENAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd < 0) { perror("open"); exit(1); }
    printf("File '%s' created successfully.\n", FILENAME);

    Employee employees[] = {
        {1, "Ravi Kumar",  "Engineer"},
        {2, "Sneha Reddy", "Manager"},
        {3, "Arjun Mehta", "Analyst"},
    };

    for (int i = 0; i < 3; i++) {
        write_record(fd, &employees[i]);
        printf("Written: ID=%d Name=%s Role=%s\n",
               employees[i].id, employees[i].name, employees[i].role);
    }

    Employee updated = {2, "Sneha Reddy", "Senior Manager"};
    update_record(fd, 1, &updated);
    printf("\nUpdated record at index 1 role to: %s\n", updated.role);

    printf("\n--- All Records ---\n");
    for (int i = 0; i < 3; i++) {
        Employee emp;
        read_record(fd, i, &emp);
        printf("ID: %d | Name: %-20s | Role: %s\n", emp.id, emp.name, emp.role);
    }

    close(fd);
    printf("\nFile closed successfully.\n");
    return 0;
}
