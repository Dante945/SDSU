from turtle import Turtle
FONT = ("Courier", 24, "normal")


class Scoreboard(Turtle):
    def __init__(self):
        super().__init__()
        self.color("black")
        self.penup()
        self.hideturtle()
        self.score = 0
        self.goto((-280, 250))
        self.update()

    def update(self):
        self.clear()
        self.write(f"Level: {self.score}", "center", font=FONT)

    def level_complete(self):
        self.score += 1
        self.update()

    def game_over(self):
        self.goto(0,0)
        self.write(f"GAME OVER", "center", font=FONT)
