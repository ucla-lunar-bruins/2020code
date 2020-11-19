'''
    If we can move forward, move forward

    If we can't, pick the direction that clears the rock most quickly

    Move in this direction until:
        We can move forward again

        We can't move this direction anymore
            If this happens, flip directions and continue from line 6
'''
# Class to control motion of the rover
#   Checks its surroundings as it attempts to move toward the goal area
class Rover:
    def __init__ (self, x, y, speed, rockList):
        self.x = x
        self.y = y
        self.speed = speed
        self.rockList = rockList
        self.status = "F"
        self.offset = 0
        self.currRock = rockList[0]
        # This value is true when we have already flipped directions once without moving forward
        #   If we have flipped once and need to flip again, it's time to backtrack
        self.flipped = False
        # This value stores the direction we want to go when done backtracking
        self.preferredDir = ""

    # Move the rover exactly 'speed' units in a direction. Update offset as needed
    def step(self, direction):
        if direction == "L":
            self.x -= self.speed
            self.offset -= self.speed
        elif direction == "R":
            self.x += self.speed
            self.offset += self.speed
        elif direction == "F":
            self.y -= self.speed
        elif direction == "B":
            self.y += self.speed

    # Checks if the passed coordinates would have the rover and rock collide
    def collide(self, x, y, rock):
        if ( x <= rock.x + 100 and x + 50 >= rock.x ) and ( y <= rock.y + 100 and y + 50 >= rock.y ):
            return True
        else:
            return False

    # Checks whether the rover is clear to move in the given direction
    def clear(self, direction):
        if direction == "F":
            for rock in self.rockList:
                if self.collide(self.x, self.y - self.speed, rock):
                    self.currRock = rock
                    return False
        elif direction == "B":
            for rock in self.rockList:
                if self.collide(self.x, self.y + self.speed, rock):
                    return False
        elif direction == "L":
            for rock in self.rockList:
                if self.collide(self.x - self.speed, self.y, rock):
                    return False
        elif direction == "R":
            for rock in self.rockList:
                if self.collide(self.x + self.speed, self.y, rock):
                    return False

        return True

    # Returns the opposite of direction
    def rev(self, direction):
        if direction == "L":
            return "R"
        elif direction == "R":
            return "L"
        elif direction == "F":
            return "B"
        elif direction == "B":
            return "F"

    # Return the direction that more quickly clears the obstacle directly in front
    def whichSideCloser(self):
        if self.x < self.currRock.x:
            return "L"
        else:
            return "R"

    # Attempt a single move. Prioritize movement forward
    def move(self):
        if self.status == "B":
            if self.clear(self.preferredDir):
                self.status = self.preferredDir
                self.step(self.preferredDir)
            elif self.clear("B"):
                self.step("B")
            else:
                # We've backtracked as far as we can, now try the other direction
                self.status = "F"
        
        elif self.clear("F"):
            self.status = "F"
            self.step("F")

            # This checks if we've successfully found a new path via backtracking
            if self.clear(self.preferredDir):
                self.flipped = False

        else:
            # If our last move was forward, pick the direction that clears the rock more quickly
            if self.status == "F":
                dir = self.whichSideCloser()
            
            # Otherwise, continue the way we were going
            else:
                dir = self.status
           
            # If we can travel in preferred direction, do so
            if self.clear(dir):
                self.status = dir
                self.step(dir)

            # If that fails, try the opposite direction (if we haven't flipped recently)
            elif self.clear(self.rev(dir)) and not self.flipped:
                self.flipped = True
                self.status = self.rev(dir)
                self.step(self.rev(dir))
            
            # Otherwise, it's time to backtrack, prioritizing the preferred direction
            else:
                self.preferredDir = dir
                self.status = "B"
                self.step("B")
