#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 1000
#define PIN_LENGTH 4

// Structure for customer details
struct customer {
  int id;
  char name[50];
  char address[100];
  long int phone_number;
};

// Structure for account details
struct account {
  int number;
  int customer_id;
  float balance;
  char pin[PIN_LENGTH + 1];
};

// Structure for transaction details
struct transaction {
  int id;
  int account_number;
  char type[20];
  float amount;
  char date[20];
};

// Global arrays for storing customer, account, and transaction details
struct customer customers[MAX_CUSTOMERS];
struct account accounts[MAX_ACCOUNTS];
struct transaction transactions[MAX_TRANSACTIONS];

// Global variables for keeping track of the number of customers, accounts, and transactions
int num_customers = 0;
int num_accounts = 0;
int num_transactions = 0;

// Function to create a new customer
void create_customer() {
  struct customer c;
  printf("Enter customer details:\n");
  printf("ID: ");
  scanf("%d", & c.id);
  printf("Name: ");
  scanf(" %[^\n]s", c.name);
  printf("Address: ");
  scanf(" %[^\n]s", c.address);
  printf("Phone number: ");
  scanf("%ld", & c.phone_number);
  customers[num_customers++] = c;
  printf("Customer created successfully!\n");
}

// Function to create a new account
void create_account() {
  struct account a;
  printf("Enter account details:\n");
  printf("Customer ID: ");
  scanf("%d", & a.customer_id);
  printf("PIN (4 digits): ");
  scanf("%s", a.pin);
  printf("Initial balance: ");
  scanf("%f", & a.balance);
  a.number = 1000 + num_accounts;
  accounts[num_accounts++] = a;
  printf("Account created successfully!\n");
}

// Function to deposit money into an account
void deposit() {
  int account_number;
  float amount;
  printf("Enter account number: ");
  scanf("%d", & account_number);
  for (int i = 0; i < num_accounts; i++) {
    if (accounts[i].number == account_number) {
      printf("Enter amount to deposit: ");
      scanf("%f", & amount);
      accounts[i].balance += amount;
      transactions[num_transactions].id = 1000 + num_transactions;
      transactions[num_transactions].account_number = account_number;
      strcpy(transactions[num_transactions].type, "DEPOSIT");
      transactions[num_transactions].amount = amount;
      // Get current date and time
      time_t t = time(NULL);
      struct tm tm = * localtime( & t);
      sprintf(transactions[num_transactions].date, "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
      num_transactions++;
      printf("Deposit successful!\n");
      return;
    }
  }
  printf("Invalid account number\n");
}

// Function to withdraw money from an account
void view_balance() {
  int account_number;
  char pin[PIN_LENGTH + 1];
  printf("Enter account number: ");
  scanf("%d", & account_number);
  for (int i = 0; i < num_accounts; i++) {
    if (accounts[i].number == account_number) {
      printf("Enter PIN: ");
      scanf("%s", pin);
      if (strcmp(pin, accounts[i].pin) == 0) {
        printf("Balance: %.2f\n", accounts[i].balance);
        return;
      } else {
        printf("Invalid PIN\n");
        return;
      }
    }
  }
  printf("Invalid account number\n");
}

// Function to view transaction history for an account
void view_transaction_history() {
  int account_number;
  char pin[PIN_LENGTH + 1];
  printf("Enter account number: ");
  scanf("%d", & account_number);
  for (int i = 0; i < num_accounts; i++) {
    if (accounts[i].number == account_number) {
      printf("Enter PIN: ");
      scanf("%s", pin);
      if (strcmp(pin, accounts[i].pin) == 0) {
        printf("Transaction history:\n");
        printf("ID\tAccount\tType\tAmount\tDate\n");
        for (int j = 0; j < num_transactions; j++) {
          if (transactions[j].account_number == account_number) {
            printf("%d\t%d\t%s\t%.2f\t%s\n", transactions[j].id, transactions[j].account_number, transactions[j].type, transactions[j].amount, transactions[j].date);
          }
        }
        return;
      } else {
        printf("Invalid PIN\n");
        return;
      }
    }
  }
  printf("Invalid account number\n");
}

// Function to verify PIN for an account
int verify_pin(int account_number, char * pin) {
  for (int i = 0; i < num_accounts; i++) {
    if (accounts[i].number == account_number) {
      if (strcmp(pin, accounts[i].pin) == 0) {
        return 1;
      } else {
        return 0;
      }
    }
  }
  return 0;
}

// Main function
int main() {
  int choice;
  do {
    printf("\nATM Banking System\n");
    printf("-------------------\n");
    printf("1. Create a new customer\n");
    printf("2. Create a new account\n");
    printf("3. Deposit money into an account\n");
    printf("4. Withdraw money from an account\n");
    printf("5. View balance for an account\n");
    printf("6. View transaction history for an account\n");
    printf("7. Exit\n");
    printf("Enter choice: ");
    scanf("%d", & choice);
    switch (choice) {
    case 1:
      create_customer();
      break;
    case 2:
      create_account();
      break;
    case 3:
      deposit();
      break;
    case 4:
      withdraw();
      break;
    case 5:
      view_balance();
      break;
    case 6:
      view_transaction_history();
      break;
    case 7:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice\n");
      break;
    }
  } while (choice != 7);
  return 0;
}