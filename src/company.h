// company.h

#ifndef COMPANY_H
#define COMPANY_H

#define MAX_NAME_LENGTH 100
#define MAX_LOC_LENGTH 50
#define MAX_COMPANIES 100

// Enumeration for company categories
typedef enum
{
    MICRO,
    PME,
    GRANDE_EMPRESA
} Category;

// Enumeration for business sectors
typedef enum
{
    AGRICULTURA,
    ELETRICIDADE_GAS_AGUA,
    TEXTEIS_VESTUARIO,
    CONSTRUCAO,
    BANCOS_SEGUROS
} BusinessSector;

typedef struct
{
    int NIF;
    char name[MAX_NAME_LENGTH];
    Category category;
    BusinessSector sector;
    char street[MAX_LOC_LENGTH];
    char locality[MAX_LOC_LENGTH];
    char postalCode[MAX_LOC_LENGTH];
    int isActive;

    // Ratings
    int numRatings;
    double totalRating;
} Company;

void createCompany(Company *company, int NIF, const char *name, Category category,
                   BusinessSector sector, const char *street, const char *locality,
                   const char *postalCode);

void createCompanyAdmin(Company *companies, int *numCompanies);

void rateCompany(Company *company, int rating);

double getAverageRating(const Company *company);

void displayCompany(const Company *company);

static int findCompanyByNIF(const Company *companies, int numCompanies, int targetNIF);

static void removeCompany(Company *companies, int *numCompanies, int index);

void listCompanies(const Company *companies, int numCompanies);

void deleteCompany(Company *companies, int *numCompanies);

#endif // COMPANY_H
