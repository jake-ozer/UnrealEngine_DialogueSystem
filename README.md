# (In Progress) Dialogue System — Unreal Engine

A flexible, data-driven dialogue system for Unreal Engine designed to handle branching conversations, NPC interactions, and narrative-driven gameplay.

---

## Features

- **Branching Dialogue Trees** — Support for multi-path conversations
- **Data Driven Integration** — Dialogue content stored in JSON files for extendability to tooling.
- **Blueprint-Friendly** — Exposed to Blueprints for designer workflows
- **Decoupled NPCs and Quests** - One NPC can be a part of many quests
- **Variable Conditions** — Show/hide dialogue choices based on dialogue state

---

## Built With
- Blueprints / C++

---

## C++ Dialogue Backend Location in Project

To see the C++ extensions I have made beyond the boilerplate Unreal FPS template, follow the path below:
```
Content/Source/FP_DialogueSystem/DialogueSystem
```

---

## How It Works

1. Formatted JSON files include the raw dialogue data for each choice in a quest.
2. Quests get parsed from JSON files, live during runtime and wait for a callback (OnDialogueUIOpened)
3. Quests hand off their current state and choice data to Dialogue UI for display.
4. Player interacts with NPC, modifies quest state independently.

---

## Screenshots

> https://jake-ozer.github.io/DevPortfolio/UDS_Thumbnail3.png
> https://jake-ozer.github.io/DevPortfolio/UDS_media/UDS_NPCTalk.gif

---
