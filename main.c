
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 200
#define MAX_TOKEN 50

// Simple bilingual (English & Tamil) keyword-based mental wellness chatbot.
// Choose language at start. Then type messages; type "exit" to quit.

void toLowerStr(char *s) {
    for (int i = 0; s[i]; i++) s[i] = (char)tolower((unsigned char)s[i]);
}

// check if any keyword in token array appears in the input (case-insensitive)
int contains_keyword(const char *input, const char *keywords[]) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strstr(input, keywords[i]) != NULL) return 1;
    }
    return 0;
}

void print_help(int lang) {
    if (lang == 1) { // English
        printf("Type any message about how you feel (e.g., 'I am stressed', 'I cannot sleep').\n");
        printf("Commands: help, tip, quote, exit\n");
    } else { // Tamil
        printf("உங்கள் உணர்ச்சிகளை இங்கே எழுதுங்கள் (உதா: 'நான் மனஅழுத்தத்தில் இருக்கிறேன்').\n");
        printf("பயன்பாட்டு சொற்கள்: help, tip, quote, exit\n");
    }
}

int main() {
    char input[MAX_INPUT];
    int lang = 1; // 1 = English, 2 = Tamil

    printf("Mental Wellness ChatBot (Text-Based) - C\n");
    printf("Choose language / மொழியை தேர்வு செய்யவும்:\n");
    printf("1. English\n2. தமிழ் (Tamil)\n");
    printf("Enter 1 or 2: ");
    if (fgets(input, sizeof(input), stdin) == NULL) return 0;
    if (strchr(input, '2') != NULL) lang = 2;

    if (lang == 1) {
        printf("\nHello! I'm your wellness companion. Type 'help' for commands.\n");
    } else {
        printf("\nவணக்கம்! நான் உங்கள் மனநல தோழன். 'help' என தட்டச்சு செய்யுங்கள்.\n");
    }

    print_help(lang);

    // keyword lists (lowercase)
    const char *stress_kw[] = {"stress", "stressed", "anxiety", "anxious", "tension", NULL};
    const char *sleep_kw[]  = {"sleep", "insomnia", "tired", "rest", "sleepless", NULL};
    const char *sad_kw[]    = {"sad", "depressed", "unhappy", "down", "lonely", NULL};
    const char *happy_kw[]  = {"happy", "good", "great", "joy", "excited", NULL};
    const char *panic_kw[]  = {"panic", "panic attack", "breathless", NULL};

    // Tamil keywords (in transliteration and some Tamil words)
    const char *stress_t_kw[] = {"manaaluttut", "manasikam", "அழுத்தம்", "மன அழுத்தம்", NULL};
    const char *sleep_t_kw[]  = {"kanavil", "nidra", "உறக்கம்", "தூக்கம்", NULL};
    const char *sad_t_kw[]    = {"துயரம்", "மனச்சோர்வு", "அழுகிறது", NULL};
    const char *happy_t_kw[]  = {"மகிழ்ச்சி", "சந்தோஷம்", NULL};

    while (1) {
        printf("\n> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        // remove newline
        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;

        // exit
        if (strcasecmp(input, "exit") == 0) {
            if (lang == 1) printf("Take care! If you need help, reach out to someone you trust. Goodbye.\n");
            else printf("கவனமாக இருங்கள்! ஆதரவு தேவைப்பட்டால் யாரோரை அணுகுங்கள். விடைபெறலாம்.\n");
            break;
        }

        // help
        if (strcasecmp(input, "help") == 0) {
            print_help(lang);
            continue;
        }

        // tip
        if (strcasecmp(input, "tip") == 0) {
            if (lang == 1) printf("Tip: Try deep-breathing for 2 minutes, take a short walk, or drink water.\n");
            else printf("சுட்டுரை: 2 நிமிடங்கள் ஆழ்ந்த மூச்சு பயிற்சி, சிறிய நடை, அல்லது தண்ணீர் குடிக்கவும்.\n");
            continue;
        }

        // quote
        if (strcasecmp(input, "quote") == 0) {
            if (lang == 1) printf("\"This too shall pass.\" Remember to be kind to yourself.\n");
            else printf("\"இதும் காலமானால் நன்றாகும்.\" நீங்களே பராமரிக்கவும்.\n");
            continue;
        }

        // For pattern matching, convert a lowercase copy
        char low[MAX_INPUT];
        strncpy(low, input, sizeof(low)-1);
        low[sizeof(low)-1] = '\0';
        toLowerStr(low);

        // English checks
        if (lang == 1) {
            if (contains_keyword(low, stress_kw) || contains_keyword(low, panic_kw)) {
                printf("I hear you're feeling stressed. Try this: 4-4-8 breathing - inhale 4s, hold 4s, exhale 8s. Would you like a short guided breathing? (yes/no)\n");
                // read simple reply
                char ans[20];
                if (fgets(ans, sizeof(ans), stdin) == NULL) break;
                ans[strcspn(ans, "\n")] = 0;
                toLowerStr(ans);
                if (strcmp(ans, "yes") == 0) {
                    printf("Let's try: Inhale... 1..2..3..4\n");
                    printf("Hold... 1..2..3..4\n");
                    printf("Exhale... 1..2..3..4..5..6..7..8\n");
                    printf("Repeat this a few times and notice your body relaxing.\n");
                } else {
                    printf("Okay. Remember short walks and stretching can help too.\n");
                }
                continue;
            }
            if (contains_keyword(low, sleep_kw)) {
                printf("Sleep problems can be tough. Try avoiding screens 30 mins before bed, and keep a consistent sleep time.\n");
                continue;
            }
            if (contains_keyword(low, sad_kw)) {
                printf("I'm sorry you're feeling low. It can help to name one small thing that felt okay today, or to talk with a friend. Do you want a motivational quote? (yes/no)\n");
                char ans[20];
                if (fgets(ans, sizeof(ans), stdin) == NULL) break;
                ans[strcspn(ans, "\n")] = 0;
                toLowerStr(ans);
                if (strcmp(ans, "yes") == 0) printf("Quote: 'You are not a drop in the ocean. You are the entire ocean in a drop.'\n");
                else printf("Okay. It's brave to share how you feel.\n");
                continue;
            }
            if (contains_keyword(low, happy_kw)) {
                printf("That's great to hear! Keep doing what brings you joy. Would you like a suggestion for self-care? (yes/no)\n");
                char ans[20];
                if (fgets(ans, sizeof(ans), stdin) == NULL) break;
                ans[strcspn(ans, "\n")] = 0;
                toLowerStr(ans);
                if (strcmp(ans, "yes") == 0) printf("Try spending 10 minutes doing a hobby: drawing, music, or a short walk.\n");
                else printf("Nice. Stay well!\n");
                continue;
            }
            // default fallback
            printf("I may not fully understand, but I'm here to listen. You can type 'tip' for quick coping ideas or 'quote' for inspiration.\n");
            continue;
        }

        // Tamil checks (basic handling)
        if (lang == 2) {
            if (contains_keyword(low, stress_t_kw)) {
                printf("நீங்கள் மனஅழுத்தத்தை உணர்கிறீர்கள். சிறு மூச்சுத்தடங்களை முயற்சி செய்யலாம்: ஆழமாய் மூச்சு 4, வைக்க 4, வெளியே விட 8. அதற்கு தேவையா? (ஆம்/இல்லை)\n");
                char ans[20];
                if (fgets(ans, sizeof(ans), stdin) == NULL) break;
                ans[strcspn(ans, "\n")] = 0;
                toLowerStr(ans);
                if (strcmp(ans, "ஆம்") == 0 || strcmp(ans, "tamam") == 0 || strcmp(ans, "yes") == 0) {
                    printf("முதல்: மெய்ப்பூர்வமாக மூச்சு இழுத்து... 1..2..3..4\n");
                    printf("வைக்க... 1..2..3..4\n");
                    printf("வெளியே விட... 1..2..3..4..5..6..7..8\n");
                    printf("இதை சில முறை இருமுறை செய்து உங்கள் உடலாற்றத்தை கவனியுங்கள்.\n");
                } else {
                    printf("நல்லது. சிறிய நடை அல்லது நீட்டிப்பும் உதவும்.\n");
                }
                continue;
            }
            if (contains_keyword(low, sleep_t_kw)) {
                printf("தூக்கம் குறைவு? படுக்கைக்கு முன் திரைபரப்பை தவிர்க்கவும் மற்றும் ஒரே நேரத்தில் தூங்க முயற்சிக்கவும்.\n");
                continue;
            }
            if (contains_keyword(low, sad_t_kw)) {
                printf("உங்களுக்கு துயரம் உணர்வாக இருந்தால், ஒரு சிறிய நல்ல விஷயத்தை நினைவில் கொள்ள முயற்சிக்கவும் அல்லது நம்பத்தகுந்த ஒருவருடன் பேசுங்கள். அதிர்ஷ்டம் வேண்டுமா? (ஆம்/இல்லை)\n");
                char ans[20];
                if (fgets(ans, sizeof(ans), stdin) == NULL) break;
                ans[strcspn(ans, "\n")] = 0;
                toLowerStr(ans);
                if (strcmp(ans, "ஆம்") == 0) printf("உரை: 'நீங்கள் தனியாக இல்லை; உதவி கிடைக்கலாம்.'\n");
                else printf("சரி. பகிர்ந்துகொள்வது தைரியம்.\n");
                continue;
            }
            if (contains_keyword(low, happy_t_kw)) {
                printf("அது நன்று! உங்கள் சந்தோஷத்தை பராமரிக்க ஒரு சிறிய சுய பராமரிப்பு செயற்கூறு வேண்டும் என்று நினைக்கிறீர்களா? (ஆம்/இல்லை)\n");
                char ans[20];
                if (fgets(ans, sizeof(ans), stdin) == NULL) break;
                ans[strcspn(ans, "\n")] = 0;
                toLowerStr(ans);
                if (strcmp(ans, "ஆம்") == 0) printf("10 நிமிடங்கள் உங்கள் விருப்பமான செயலில் செலவிடுங்கள்: இசை, ஓவியம் அல்லது நடை.\n");
                else printf("சிறந்தது. நலமாக இருங்கள்!\n");
                continue;
            }
            printf("நான் முழுமையாக புரிந்துகொள்ளக்கூடாது, ஆனால் கேட்க நான் இங்கே இருக்குகிறேன். 'tip' அல்லது 'quote' தட்டச்சு செய்யவும்.\n");
            continue;
        }
    }

    return 0;
}
