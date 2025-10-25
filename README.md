# Mental Wellness ChatBot (Text-Based) - C

A simple bilingual (English + Tamil) text-based mental wellness chatbot implemented in C.  
This mini project demonstrates a basic keyword-driven chatbot that offers coping tips, motivational quotes, and short guided breathing exercises. It is designed as a friendly companion and is **NOT** a replacement for professional mental health care.

## Features
- Bilingual support: English and Tamil (user selects language at start).
- Keyword-based responses for common concerns: stress, sleep, sadness, happiness.
- Commands: `help`, `tip`, `quote`, `exit`.
- Lightweight C program suitable for terminal/CLI use.
- Aligns with **SDG 3 – Good Health and Well‑Being** by promoting mental health awareness.

## Files
- `main.c` — C source code for the chatbot.
- `responses.txt` — sample tips and messages used for reference.
- `README.md` — this document.

## How to compile & run
```bash
gcc main.c -o mental_chatbot
./mental_chatbot
```

## Usage
1. Run the program.
2. Choose language (1 = English, 2 = Tamil).
3. Type your message (or `help`, `tip`, `quote`).
4. Type `exit` to quit.

## Extend ideas
- Add a larger response database and load from file.
- Implement frequency-based suggestion or simple learning.
- Add logging (with user consent) and analytics for usage patterns.
- Integrate with external APIs or a GUI for broader reach.

## Safety & Support
This chatbot offers supportive messages and coping strategies. If you or someone is at risk or in crisis, please seek professional help or contact local emergency/helpline services.

Developed by Loki.
