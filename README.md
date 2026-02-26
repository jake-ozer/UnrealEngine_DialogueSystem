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

```
Content/Source/FP_DialogueSystem/DialogueSystem
```

---

## How It Works

1. **Dialogue Data** is defined in a Data Table using a custom `FDialogueRow` struct — each row contains speaker name, dialogue text, response options, and optional event tags.
2. **The Dialogue Manager** (a Game Instance subsystem or Actor component) reads from the Data Table and drives the conversation flow.
3. **NPC Actors** hold a reference to their starting dialogue row key. On interaction, they pass this to the Dialogue Manager.
4. **The Dialogue Widget** renders the current line and player choices, and calls back into the Manager on player selection.

---

## Screenshots

> https://jake-ozer.github.io/DevPortfolio/UDS_Thumbnail3.png
> https://jake-ozer.github.io/DevPortfolio/UDS_media/UDS_NPCTalk.gif

---
