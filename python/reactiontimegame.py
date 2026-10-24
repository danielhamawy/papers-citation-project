import tkinter as tk
import random
import time

TOTAL_ROUNDS = 10
round_count = 0
start_time = 0
reaction_times = []

def show_box():
    global start_time
    x = random.randint(50, 350)
    y = random.randint(50, 350)

    canvas.coords(box, x, y, x+60, y+60)
    canvas.itemconfig(box, state="normal")

    start_time = time.time()

def next_round():
    if len(reaction_times) < TOTAL_ROUNDS:
        delay = random.randint(1000, 3000)  # random interval (1–3 seconds)
        root.after(delay, show_box)
    else:
        show_results()

def click_box(event):
    global round_count

    reaction = time.time() - start_time
    reaction_times.append(reaction)

    canvas.itemconfig(box, state="hidden")

    round_count += 1
    round_label.config(text=f"Round: {round_count}/{TOTAL_ROUNDS}")

    next_round()

def show_results():
    avg = sum(reaction_times) / len(reaction_times)
    canvas.delete("all")

    result_text = f"Game Over!\nAverage Reaction Time:\n{avg:.3f} seconds"
    canvas.create_text(200, 200, text=result_text, font=("Arial", 18))

# window
root = tk.Tk()
root.title("Reaction Time Game")
root.geometry("400x450")

round_label = tk.Label(root, text="Round: 0/10", font=("Arial", 16))
round_label.pack()

canvas = tk.Canvas(root, width=400, height=400, bg="white")
canvas.pack()

box = canvas.create_rectangle(50, 50, 110, 110, fill="red", state="hidden")

canvas.tag_bind(box, "<Button-1>", click_box)

root.after(2000, next_round)

root.mainloop()