import tkinter as tk
import winsound

# Create window
window = tk.Tk()
window.title("Calculator")
window.geometry("300x400")

# Entry (display)
entry = tk.Entry(window, font=("Arial", 20), borderwidth=5, relief="ridge", justify="right")
entry.pack(fill="x", padx=10, pady=10)

# Button click function
def click(value):
    entry.insert(tk.END, value)

def clear():
    entry.delete(0, tk.END)

def calculate():
    try:
        result = eval(entry.get())
        clear()
        entry.insert(0, result)
    except:
        clear()
        entry.insert(0, "Error")

# Buttons layout
buttons = [
    "7", "8", "9", "/",
    "4", "5", "6", "*",
    "1", "2", "3", "-",
    "0", ".", "=", "+"
]

frame = tk.Frame(window)
frame.pack()

row = 0
col = 0

for btn in buttons:
    if btn == "=":
        action = calculate
    else:
        action = lambda x=btn: click(x)

    tk.Button(
        frame,
        text=btn,
        width=5,
        height=2,
        font=("Arial", 14),
        command=action
    ).grid(row=row, column=col, padx=5, pady=5)

    col += 1
    if col > 3:
        col = 0
        row += 1

# Clear button
tk.Button(
    window,
    text="C",
    font=("Arial", 14),
    command=clear
).pack(fill="x", padx=10, pady=10)

def click(value):
    winsound.Beep(1000, 100)   # frequency in Hz, duration in ms
    entry.insert(tk.END, value)

window.mainloop()
