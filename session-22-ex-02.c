#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[100];
int accountCount = 0;

void docFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file != NULL) {
        while (fread(&accounts[accountCount], sizeof(Account), 1, file)) {
            accountCount++;
        }
        fclose(file);
    }
}

void ghiFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}

int kiemTraTaiKhoanTonTai(char *username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void dangKy() {
    char username[50], password[50], confirmPassword[50];

    printf("Nhap tai khoan: ");
    scanf("%s", username);

    if (kiemTraTaiKhoanTonTai(username)) {
        printf("Tai khoan da ton tai. Vui long chon tai khoan khac.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", password);
    
    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Mat khau khong khop. Vui long nhap lai.\n");
        return;
    }

    Account newAccount;
    strcpy(newAccount.username, username);
    strcpy(newAccount.password, password);

    accounts[accountCount++] = newAccount;
    ghiFile();
    printf("Dang ky thanh cong!\n");
}

void dangNhap() {
    char username[50], password[50];

    printf("Nhap tai khoan: ");
    scanf("%s", username);

    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong!\n");
            return;
        }
    }

    printf("Tai khoan hoac mat khau sai. Vui long kiem tra lai.\n");
}

void hienThiMenu() {
    printf("\nMENU\n");
    printf("1. Dang nhap\n");
    printf("2. Dang ky\n");
    printf("3. Thoat\n");
}

int main() {
    int choice;
    docFile();

    do {
        hienThiMenu();
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                dangNhap();
                break;
            case 2:
                dangKy();
                break;
            case 3:
                printf("Thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai!\n");
        }
    } while (choice != 3);

    return 0;
}
