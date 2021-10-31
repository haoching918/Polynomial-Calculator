#include "polynomial.h"
#include "compute.h"

int32_t main()
{
    printf("Polynomial Calculator\n");
    while (1)
    {
        menu();
        int32_t option = -1;
        printf("Please enter option: ");
        scanf("%d", &option);
        CLEARBUF
        switch (option)
        {
        case 1:
            init_poly();
            break;
        case 2:
            show_poly();
            break;
        case 3:
            coef();
            break;
        case 4:
            add_delete_term();
            break;
        case 5:
            addition();
            break;
        case 6:
            subtraction();
            break;
        case 7:
            multiplication();
            break;
        case 8:
            division();
            break;
        case 9:
            show_nameBook();
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}