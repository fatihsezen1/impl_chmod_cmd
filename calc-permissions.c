#include <stddef.h>
#include "calc-permissions.h"

int CalculatePermissionValue(char permission)
{
    switch (permission) {
        case 'r': return 4;
        case 'w': return 2;
        case 'x': return 1;
        default: return 0;
    }
}

void ParsePermissions(const char *input, int *user, int *group, int *others)
{
    *user = *group = *others = 0;
    if (input == NULL)
        return;

    for (int i = 0; input[i] != '\0'; ++i) {
        if ((input[i] == 'u' || input[i] == 'g' || input[i] == 'o') && (input[i + 1] == '+')) {
            //u+r format
            int j = i + 2; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[i] == 'u') *user += value;
                if (input[i] == 'g') *group += value;
                if (input[i] == 'o') *others += value;
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if ((input[i] == 'u' || input[i] == 'g' || input[i] == 'o') && (input[i + 1] == '-')){
            //u-r format
            int j = i + 2; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[i] == 'u') *user -= value;
                if (input[i] == 'g') *group -= value;
                if (input[i] == 'o') *others -= value;
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if ((input[i + 1] == 'u' || input[i + 1] == 'g' || input[i + 1] == 'o') && (input[i + 2] == '+')) {
            //ug+r format
            int j = i + 3; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[i] == 'u') *user += value;
                if (input[i] == 'g') *group += value;
                if (input[i] == 'o') *others += value;
                if (input[i + 1] == 'u') *user += value;
                if (input[i + 1] == 'g') *group += value;
                if (input[i + 1] == 'o') *others += value;
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if ((input[i + 1] == 'u' || input[i + 1] == 'g' || input[i + 1] == 'o') && (input[i + 2] == '-')) {
            //ug-r format
            int j = i + 3; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[i] == 'u') *user -= value;
                if (input[i] == 'g') *group -= value;
                if (input[i] == 'o') *others -= value;
                if (input[i + 1] == 'u') *user -= value;
                if (input[i + 1] == 'g') *group -= value;
                if (input[i + 1] == 'o') *others -= value;
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if ((input[i + 2] == 'u' || input[i + 2] == 'g' || input[i + 2] == 'o') && (input[i + 3] == '+')) {
            //ugo+r format
            int j = i + 3; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[i] == 'u') *user += value;
                if (input[i] == 'g') *group += value;
                if (input[i] == 'o') *others += value;
                if (input[i + 1] == 'u') *user += value;
                if (input[i + 1] == 'g') *group += value;
                if (input[i + 1] == 'o') *others += value;
                if (input[i + 2] == 'u') *user += value;
                if (input[i + 2] == 'g') *group += value;
                if (input[i + 2] == 'o') *others += value;
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if ((input[i + 2] == 'u' || input[i + 2] == 'g' || input[i + 2] == 'o') && (input[i + 3] == '-')) {
            //ugo-r format
            int j = i + 3; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[i] == 'u') *user -= value;
                if (input[i] == 'g') *group -= value;
                if (input[i] == 'o') *others -= value;
                if (input[i + 1] == 'u') *user -= value;
                if (input[i + 1] == 'g') *group -= value;
                if (input[i + 1] == 'o') *others -= value;
                if (input[i + 2] == 'u') *user -= value;
                if (input[i + 2] == 'g') *group -= value;
                if (input[i + 2] == 'o') *others -= value;
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
            
        }
        else if ((input[i] == 'a') && (input[i + 1] == '+')) {
            //a+rwx format
            int j = i + 1; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[j] == 'a') {
                    *user +=value;
                    *group +=value;
                    *others +=value;
                }
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if ((input[i] == 'a') && (input[i + 1] == '-')) {
            //a-rwx format
            int j = i + 1; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[j] == 'a') {
                    *user -=value;
                    *group -=value;
                    *others -=value;
                }
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if (input[i] == '+') {
            //+rwx format
            int j = i; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[j] == 'a') {
                    *user +=value;
                    *group +=value;
                    *others +=value;
                }
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
        else if (input[i] == '-') {
            //-rwx format
            int j = i; //start checking permissions after '+'
            while (input[j] != '\0' && input[j] != 'u' && input[j] != 'g' && input[j] != 'o') {
                int value = CalculatePermissionValue(input[j]);
                if (input[j] == 'a') {
                    *user -=value;
                    *group -=value;
                    *others -=value;
                }
                j++;
            }
            i = j - 1; //skip past the permissions we just processed
        }
    }
}