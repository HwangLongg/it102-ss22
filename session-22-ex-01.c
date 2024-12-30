#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[100];
    int age;
} Student;

Student students[100]; 
int studentCount = 0;

void loadFromFile() {
    FILE *file = fopen("students.dat", "rb");
    if (file) {
        fread(&studentCount, sizeof(int), 1, file);
        fread(students, sizeof(Student), studentCount, file);
        fclose(file);
    }
}

void saveToFile() {
    FILE *file = fopen("students.dat", "wb");
    if (file) {
        fwrite(&studentCount, sizeof(int), 1, file);
        fwrite(students, sizeof(Student), studentCount, file);
        fclose(file);
    }
}

void printStudentList() {
    if (studentCount == 0) {
        printf("Danh sach sinh vien rong!\n");
        return;
    }
    printf("\nDanh sach sinh vien:\n");
    printf("ID\t\tTen\t\t\tTuoi\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%d\t\t%s\t\t\t%d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent() {
    if (studentCount >= 100) {
        printf("Danh sach sinh vien da day!\n");
        return;
    }
    
    Student newStudent;
    printf("Nhap ID sinh vien: ");
    scanf("%d", &newStudent.id);
    getchar();
    printf("Nhap ten sinh vien: ");
    fgets(newStudent.name, 100, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    printf("Nhap tuoi sinh vien: ");
    scanf("%d", &newStudent.age);

    students[studentCount] = newStudent;
    studentCount++;
    saveToFile();
    printf("Them sinh vien thanh cong!\n");
}

void editStudent() {
    int id;
    printf("Nhap ID sinh vien muon sua: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Nhap ten moi sinh vien: ");
            getchar();
            fgets(students[i].name, 100, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi sinh vien: ");
            scanf("%d", &students[i].age);
            saveToFile();
            printf("Sua thong tin sinh vien thanh cong!\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID %d\n", id);
    }
}

void deleteStudent() {
    int id;
    printf("Nhap ID sinh vien muon xoa: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveToFile();
            printf("Xoa sinh vien thanh cong!\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien voi ID %d\n", id);
    }
}

void searchStudent() {
    char name[100];
    printf("Nhap ten sinh vien muon tim: ");
    getchar();
    fgets(name, 100, stdin);
    name[strcspn(name, "\n")] = '\0';

    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strstr(students[i].name, name) != NULL) {
            if (!found) {
                printf("\nKet qua tim kiem:\n");
                printf("ID\t\tTen\t\t\tTuoi\n");
            }
            printf("%d\t\t%s\t\t\t%d\n", students[i].id, students[i].name, students[i].age);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sinh vien co ten '%s'\n", name);
    }
}

void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].age > students[j].age) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Danh sach sinh vien sau khi sap xep:\n");
    printStudentList();
}

void displayMenu() {
    printf("\nMENU\n");
    printf("1. In danh sach sinh vien\n");
    printf("2. Them sinh vien\n");
    printf("3. Sua thong tin sinh vien\n");
    printf("4. Xoa sinh vien\n");
    printf("5. Tim kiem sinh vien\n");
    printf("6. Sap xep danh sach sinh vien\n");
    printf("7. Thoat\n");
}

int main() {
    loadFromFile();

    int choice;
    do {
        displayMenu();
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudentList();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (choice != 7);

    return 0;
}
