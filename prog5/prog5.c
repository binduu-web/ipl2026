#include <stdio.h>
#include <stdlib.h>

union decision {
    unsigned char flags;
    struct field {
        int your_choice:1;           // bit 0
        int your_mothers_choice:1;   // bit 1
        int your_fathers_choice:1;   // bit 2
        int socially_acceptable:1;   // bit 3
        int financially_viable:1;    // bit 4
        int do_you_aptitude:1;       // bit 5
        int do_you_likeit:1;         // bit 6
        int decision:1;              // bit 7 (computed)
    };
};

union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void print_conclusion_based_on_flags(union decision d);

int main() {
    union decision my_decision;
    
    printf("=== DECISION MAKING SYSTEM ===\n\n");
    
    // Get input from user
    my_decision = input();
    
    // Make the decision
    make_decision(&my_decision);
    
    // Print the narrative
    printf("\n");
    print_decision(my_decision);
    
    // Print conclusion based on flags
    print_conclusion_based_on_flags(my_decision);
    
    return 0;
}

union decision input() {
    union decision d;
    int response;
    
    printf("Answer YES (1) or NO (0) to each question:\n\n");
    
    printf("1. Is it YOUR CHOICE? (Do you want it?) ");
    scanf("%d", &response);
    d.your_choice = (response == 1) ? 1 : 0;
    
    printf("2. Would YOUR MOTHER approve? ");
    scanf("%d", &response);
    d.your_mothers_choice = (response == 1) ? 1 : 0;
    
    printf("3. Would YOUR FATHER approve? ");
    scanf("%d", &response);
    d.your_fathers_choice = (response == 1) ? 1 : 0;
    
    printf("4. Is it SOCIALLY ACCEPTABLE? ");
    scanf("%d", &response);
    d.socially_acceptable = (response == 1) ? 1 : 0;
    
    printf("5. Is it FINANCIALLY VIABLE? ");
    scanf("%d", &response);
    d.financially_viable = (response == 1) ? 1 : 0;
    
    printf("6. Do you have the APTITUDE for it? ");
    scanf("%d", &response);
    d.do_you_aptitude = (response == 1) ? 1 : 0;
    
    printf("7. DO YOU LIKE it? ");
    scanf("%d", &response);
    d.do_you_likeit = (response == 1) ? 1 : 0;
    
    printf("\n");
    return d;
}

void make_decision(union decision *d) {
    /* Decision formula: 
     * DO IT if: (your_choice AND do_you_likeit AND financially_viable) 
     *           AND (at least 3 of the other 4 factors are positive)
     */
    
    int positive_count = 0;
    
    // Count positive factors (excluding your_choice, do_you_likeit, financially_viable, and decision)
    positive_count += d->your_mothers_choice;
    positive_count += d->your_fathers_choice;
    positive_count += d->socially_acceptable;
    positive_count += d->do_you_aptitude;
    
    // Decision logic
    if (d->your_choice && d->do_you_likeit && d->financally_viable && positive_count >= 3) {
        d->decision = 1;  // YES, do it!
    } else {
        d->decision = 0;  // NO, don't do it
    }
}

void print_decision(union decision d) {
    printf("=== YOUR DECISION NARRATIVE ===\n\n");
    
    printf("You indicated:\n");
    printf("  • Your choice: %s\n", d.your_choice ? "YES" : "NO");
    printf("  • Mother approves: %s\n", d.your_mothers_choice ? "YES" : "NO");
    printf("  • Father approves: %s\n", d.your_fathers_choice ? "YES" : "NO");
    printf("  • Socially acceptable: %s\n", d.socially_acceptable ? "YES" : "NO");
    printf("  • Financially viable: %s\n", d.financially_viable ? "YES" : "NO");
    printf("  • Have aptitude: %s\n", d.do_you_aptitude ? "YES" : "NO");
    printf("  • You like it: %s\n", d.do_you_likeit ? "YES" : "NO");
    printf("\n");
    
    if (d.decision) {
        printf("🎉 DECISION: GO FOR IT! 🎉\n\n");
        printf("This decision aligns with your desires, is financially sound,\n");
        printf("and has strong support from the important factors.\n");
        printf("You have the aptitude and passion - success is likely!\n");
    } else {
        printf("⚠️  DECISION: RECONSIDER ⚠️\n\n");
        printf("This decision may not be the right choice right now.\n");
        
        if (!d.financially_viable) {
            printf("  • Financial concerns need to be addressed.\n");
        }
        if (!d.your_choice || !d.do_you_likeit) {
            printf("  • Make sure this is truly what YOU want.\n");
        }
        if (!d.do_you_aptitude) {
            printf("  • Consider developing the necessary skills first.\n");
        }
        printf("\nTake time to reflect or address the concerns before proceeding.\n");
    }
}

void print_conclusion_based_on_flags(union decision d) {
    printf("\n=== FLAGS ANALYSIS ===\n\n");
    printf("Flags byte value: %u (0x%02X)\n\n", d.flags, d.flags);
    
    // Interpret based on number of positive flags (excluding decision bit)
    int positive_flags = 0;
    positive_flags += d.your_choice;
    positive_flags += d.your_mothers_choice;
    positive_flags += d.your_fathers_choice;
    positive_flags += d.socially_acceptable;
    positive_flags += d.financially_viable;
    positive_flags += d.do_you_aptitude;
    positive_flags += d.do_you_likeit;
    
    printf("Positive factors: %d out of 7\n\n", positive_flags);
    
    switch(positive_flags) {
        case 7:
            printf("🌟 PERFECT SCORE! 🌟\n");
            printf("Every factor is aligned! This is a rare golden opportunity.\n");
            printf("PROCEED WITH CONFIDENCE AND ENTUSIASM!\n");
            break;
            
        case 6:
            printf("⭐ EXCELLENT! ⭐\n");
            printf("Almost everything is in your favor.\n");
            printf("Identify the one weak point and address it, then GO!\n");
            break;
            
        case 5:
            printf("✓ VERY GOOD ✓\n");
            printf("Strong positive indicators overall.\n");
            printf("This is a good decision with minor concerns to manage.\n");
            break;
            
        case 4:
            printf("⚖️  MIXED SIGNALS ⚖️\n");
            printf("You have equal positive and negative factors.\n");
            printf("Carefully weigh the pros and cons before deciding.\n");
            break;
            
        case 3:
            printf("⚠️  CAUTION ⚠️\n");
            printf("More concerns than approvals.\n");
            printf("Consider waiting or finding alternatives.\n");
            break;
            
        case 2:
            printf("🚨 STRONG CAUTION 🚨\n");
            printf("Most factors are negative.\n");
            printf("This is likely NOT the right decision.\n");
            break;
            
        case 1:
        case 0:
            printf("🛑 STOP! 🛑\n");
            printf("Almost no positive indicators.\n");
            printf("DEFINITELY DO NOT PROCEED with this decision.\n");
            printf("Reconsider your options completely.\n");
            break;
            
        default:
            printf("Invalid flag state.\n");
    }
    
    // Additional bit pattern interpretation
    printf("\n=== BIT PATTERN ===\n");
    printf("Binary: %c%c%c%c%c%c%c%c\n",
           d.decision ? '1' : '0',
           d.do_you_likeit ? '1' : '0',
           d.do_you_aptitude ? '1' : '0',
           d.financially_viable ? '1' : '0',
           d.socially_acceptable ? '1' : '0',
           d.your_fathers_choice ? '1' : '0',
           d.your_mothers_choice ? '1' : '0',
           d.your_choice ? '1' : '0');
    printf("        ↑decision ↑like ↑apt ↑money ↑social ↑father ↑mother ↑you\n");
}