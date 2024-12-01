package cn.edu.scu.cs;

import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.PriorityQueue;
import java.util.HashSet;
import java.util.Comparator;
import java.util.Random;

public class PacMan {
    // Game configuration constants
    private static final int MATRIX_ROWS = 28;
    private static final int MATRIX_COLS = 29;
    private static final int PANEL_OFFSET = 40;

    // Player initial spawn position
    private static final int INITIAL_PLAYER_ROW = 1;
    private static final int INITIAL_PLAYER_COL = 1;

    // Track game state
    private static int playerLives = 3;

    // Game matrix: 3 represents the player
    private static final int[][] gameMatrix = new int[MATRIX_ROWS][MATRIX_COLS]; // Define matrix size
    private static int playerPositionX = INITIAL_PLAYER_ROW; // Use constant for initial player row position
    private static int playerPositionY = INITIAL_PLAYER_COL; // Use constant for initial player column position
    private static final int playerRebirthX = playerPositionX;
    private static final int playerRebirthY = playerPositionY;
    // Initial positions of the ghosts
    private static int ghostStartX = 15; // Initial ghost row position
    private static int ghostStartY = 12; // Initial ghost column position
    private static long lastMoveTimestamp = 0; // Timestamp of the last move
    private static JLabel playerImageLabel; // Global variable for player image
    private static JLabel hintLabel;
    private static JLabel livesLabel;
    private static JLabel fruitCounterLabel;
    private static JPanel gamePanel; // Global variable for game panel
    private static int totalFruitCount = 0;
    private static int totalGhostCount = 0;
    private static boolean isSecondLevel = false;
    private static boolean isThirdLevel = false;
    private static boolean isFourthLevel = false;
    private static final ArrayList<Ghost> ghostList = new ArrayList<>();
    private static boolean isVictory = false;
    private static final int MOVE_STEP = 22; // Step size for each move

    // Define direction enum
    public enum Direction {
        UP, DOWN, LEFT, RIGHT
    }

    private static int collectedFruits = 0; // Track the number of fruits eaten

    private static long MOVE_DELAY = 200; // Define MOVE_DELAY

    private static int playerImageIndex = 0; // Define playerImageIndex

    private static Direction playerDirection = Direction.UP; // Define playerDirection

    // Initialize the matrix by copying the given pattern into it
    private static void initializeMatrix(int[][] targetMatrix, int[][] sourcePattern) {
        for (int i = 0; i < sourcePattern.length; i++) {
            System.arraycopy(sourcePattern[i], 0, targetMatrix[i], 0, sourcePattern[i].length);
        }
    }

    public static void createMap() {
        for (int[] row : gameMatrix) {
            Arrays.fill(row, 0);
        }
        for (int i = 10; i <= 18; i++) {
            gameMatrix[9][i] = 1; // Upper arc
            gameMatrix[19][i] = 1; // Lower arc
        }
        for (int i = 11; i <= 17; i++) {
            gameMatrix[i][10] = 1; // Left arc
            gameMatrix[i][18] = 1; // Right arc
        }

        // Radiating lines
        for (int i = 0; i < 8; i++) {
            gameMatrix[9 - i][14] = 1; // Upper radiating line
            gameMatrix[19 + i][14] = 1; // Lower radiating line
            gameMatrix[14][10 - i] = 1; // Left radiating line
            gameMatrix[14][18 + i] = 1; // Right radiating line
        }

        // Diagonal radiating lines
        for (int i = 1; i < 7; i++) {
            gameMatrix[9 - i][10 - i] = 1; // Upper left
            gameMatrix[9 - i][18 + i] = 1; // Upper right
            gameMatrix[19 + i][10 - i] = 1; // Lower left
            gameMatrix[19 + i][18 + i] = 1; // Lower right
        }

        // Wave decorations (between radiating lines)
        for (int i = 12; i <= 16; i++) {
            gameMatrix[7][i] = 1; // Upper wave
            gameMatrix[21][i] = 1; // Lower wave
        }
        for (int i = 11; i <= 17; i++) {
            gameMatrix[i][8] = 1; // Left wave
            gameMatrix[i][20] = 1; // Right wave
        }
        gameMatrix[playerPositionX][playerPositionY] = 3; // Initial player position

        gameMatrix[ghostStartX][ghostStartY] = 4; // First ghost
        gameMatrix[ghostStartX + 10][ghostStartY + 10] = 4; // Second ghost
        gameMatrix[ghostStartX - 4][ghostStartY - 4] = 4; // Third ghost

        for (int i = 15; i > 0; i--) {
            randomlyChangeZeroToTwo(); // Generate fruits
            totalFruitCount++;
        }
    }

    public static void randomlyChangeZeroToTwo() {
        ArrayList<Point> emptySpaces = new ArrayList<>();

        // Traverse the matrix and record all positions with value 0
        for (int row = 0; row < gameMatrix.length; row++) {
            for (int col = 0; col < gameMatrix[row].length; col++) {
                if (gameMatrix[row][col] == 0) {
                    emptySpaces.add(new Point(row, col));
                }
            }
        }

        // If there are empty positions, randomly select one
        if (!emptySpaces.isEmpty()) {
            Random rand = new Random();
            Point randomEmptySpace = emptySpaces.get(rand.nextInt(emptySpaces.size()));
            gameMatrix[randomEmptySpace.x][randomEmptySpace.y] = 2; // Change the position to 2
        }
    }

    public static void moveGhosts(ArrayList<Ghost> ghosts) {
        for (Ghost ghost : ghosts) {
            if (ghost.isKilled()) {
                continue;
            }
            moveGhost(ghost);
        }
    }

    // Check if the move is valid: the new position is within the matrix and not a wall
    private static boolean isValidMove(int newRow, int newCol) {
        return newRow >= 0 && newRow < gameMatrix.length
                && newCol >= 0 && newCol < gameMatrix[0].length
                && (gameMatrix[newRow][newCol] == 0 || gameMatrix[newRow][newCol] == 3);
    }

    public static void moveGhost(Ghost ghost) {
        ghost.setMovement((ghost.getMovement() + 1) % 2); // Switch animation

        if (ghost.isPaused()) {
            ghost.setStatus("Scared");
            if (System.currentTimeMillis() - ghost.getPauseStartTime() >= 3000) {
                ghost.setStatus("Ghost1");
                ghost.setPaused(false);
            } else {
                return;
            }
        }

        // Use A* algorithm to find the path to the player
        Point nextMove = findPathToPlayer(ghost.getRow(), ghost.getCol());
        if (nextMove != null) {
            int newGhostRow = nextMove.x;
            int newGhostCol = nextMove.y;

            if (isValidMove(newGhostRow, newGhostCol)) {
                gameMatrix[ghost.getRow()][ghost.getCol()] = 0;
                ghost.setRow(newGhostRow);
                ghost.setCol(newGhostCol);
                gameMatrix[ghost.getRow()][ghost.getCol()] = 4;
            }
        }
    }

    // Use A* algorithm to find the path to the player
    private static Point findPathToPlayer(int ghostRow, int ghostCol) {
        PriorityQueue<Node> openSet = new PriorityQueue<>(Comparator.comparingInt(n -> n.fCost));
        HashSet<Point> closedSet = new HashSet<>();
        openSet.add(new Node(ghostRow, ghostCol, null, 0, heuristic(ghostRow, ghostCol)));

        while (!openSet.isEmpty()) {
            Node current = openSet.poll();
            if (current.row == playerPositionX && current.col == playerPositionY) {
                return reconstructPath(current);
            }

            closedSet.add(new Point(current.row, current.col));

            for (int[] direction : new int[][] { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } }) {
                int newRow = current.row + direction[0];
                int newCol = current.col + direction[1];

                if (!isValidMove(newRow, newCol) || closedSet.contains(new Point(newRow, newCol))) {
                    continue;
                }

                int tentativeGCost = current.gCost + 1;
                Node neighbor = new Node(newRow, newCol, current, tentativeGCost, heuristic(newRow, newCol));

                if (openSet.stream().noneMatch(n -> n.row == newRow && n.col == newCol && n.gCost <= tentativeGCost)) {
                    openSet.add(neighbor);
                }
            }
        }
        return null; // No path found
    }

    private static int heuristic(int row, int col) {
        return Math.abs(row - playerPositionX) + Math.abs(col - playerPositionY);
    }

    private static Point reconstructPath(Node node) {
        while (node.parent != null && node.parent.parent != null) {
            node = node.parent;
        }
        return new Point(node.row, node.col);
    }

    private static class Node {
        int row, col;
        Node parent;
        int gCost, fCost;

        Node(int row, int col, Node parent, int gCost, int hCost) {
            this.row = row;
            this.col = col;
            this.parent = parent;
            this.gCost = gCost;
            this.fCost = gCost + hCost;
        }
    }

    public static void gameOver() {
        if (!isVictory) {
            JOptionPane.showMessageDialog(null, "Game Over!", "Game Over", JOptionPane.INFORMATION_MESSAGE);
            System.exit(0); // Exit the program
        } else {
            // Create a custom victory screen
            JLabel victoryLabel = new JLabel("Victory! Fruits eaten: " + collectedFruits, SwingConstants.CENTER);
            victoryLabel.setFont(new Font("Arial", Font.PLAIN, 20)); // Use common font Arial

            // Create a JFrame to display the message
            JFrame victoryFrame = new JFrame("Victory!");
            victoryFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            // Set layout and add JLabel
            victoryFrame.setLayout(new BorderLayout());
            victoryFrame.add(victoryLabel, BorderLayout.CENTER);

            // Set window size and center it
            victoryFrame.setSize(400, 200);
            victoryFrame.setLocationRelativeTo(null); // Center the window
            victoryFrame.setVisible(true);
        }
    }

    public static void startGame() {
        PacMan gameInstance = new PacMan();
        createMap();

        // Create 3 Ghost objects
        ghostList.add(new Ghost(ghostStartX, ghostStartY));
        ghostList.add(new Ghost(ghostStartX + 8, ghostStartY + 8)); // Slightly offset their positions
        ghostList.add(new Ghost(ghostStartX - 4, ghostStartY - 4)); // Different initial positions
        totalGhostCount += 3;

        // Image path configuration using class loader
        HashMap<String, String[]> images = new HashMap<>();

        images.put("UP", new String[] {
                "/images/PacMan2up.gif",
                "/images/PacMan3up.gif",
                "/images/PacMan4up.gif"
        });
        images.put("DOWN", new String[] {
                "/images/PacMan2down.gif",
                "/images/PacMan3down.gif",
                "/images/PacMan4down.gif"
        });
        images.put("LEFT", new String[] {
                "/images/PacMan2left.gif",
                "/images/PacMan3left.gif",
                "/images/PacMan4left.gif"
        });
        images.put("RIGHT", new String[] {
                "/images/PacMan2right.gif",
                "/images/PacMan3right.gif",
                "/images/PacMan4right.gif"
        });
        images.put("Ghost1", new String[] {
                "/images/Ghost1.gif",
                "/images/Ghost2.gif"
        });
        images.put("Scared", new String[] {
                "/images/GhostScared1.gif",
                "/images/GhostScared2.gif"
        });
        images.put("Fruit", new String[] {
                "/images/FrightFruit.png"
        });
        images.put("Life", new String[] {
                "/images/PacMan1.gif"
        });

        // Create JFrame
        JFrame frame = new JFrame("PacMan Game");
        frame.setSize(660, 660 + PANEL_OFFSET);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        // Game panel
        gamePanel = new JPanel() {
            @Override
            protected void paintComponent(Graphics g) {
                super.paintComponent(g);

                // First draw all the basic blocks and images
                for (int row = 0; row < gameMatrix.length; row++) {
                    for (int col = 0; col < gameMatrix[row].length; col++) {
                        int x = col * MOVE_STEP;
                        int y = row * MOVE_STEP + PANEL_OFFSET;

                        // First fill the black background
                        g.setColor(Color.BLACK);
                        g.fillRect(x, y, MOVE_STEP, MOVE_STEP);

                        // Draw other elements
                        if (gameMatrix[row][col] == 5) { // Portal
                            g.drawImage(loadImageIcon(images.get("Portal")[0]).getImage(),
                                    x, y, MOVE_STEP, MOVE_STEP, this);
                        } else if (gameMatrix[row][col] == 0) {
                            g.setColor(Color.YELLOW);
                            g.fillOval(x + MOVE_STEP * 7 / 16, y + MOVE_STEP * 7 / 16, MOVE_STEP / 8, MOVE_STEP / 8);
                        } else if (gameMatrix[row][col] == 2) {
                            g.drawImage(loadImageIcon(images.get("Fruit")[0]).getImage(), x, y, MOVE_STEP, MOVE_STEP,
                                    this);
                        } else if (gameMatrix[row][col] == 4) {
                            for (Ghost ghost : ghostList) {
                                if (ghost.getRow() == row && ghost.getCol() == col) {
                                    g.drawImage(
                                            loadImageIcon(images.get(ghost.getStatus())[ghost.getMovement()])
                                                    .getImage(),
                                            x, y, MOVE_STEP, MOVE_STEP, this);
                                }
                            }
                        }
                    }
                }

                // Draw all the blue boundary lines separately
                g.setColor(Color.BLUE);
                for (int row = 0; row < gameMatrix.length; row++) {
                    for (int col = 0; col < gameMatrix[row].length; col++) {
                        int x = col * MOVE_STEP;
                        int y = row * MOVE_STEP + PANEL_OFFSET;

                        // Check if the current cell is a wall
                        boolean isWall = gameMatrix[row][col] == 1;

                        // Check the upper boundary
                        if (row > 0 && (isWall != (gameMatrix[row - 1][col] == 1))) {
                            g.drawLine(x, y, x + MOVE_STEP, y);
                        }
                        // Check the lower boundary
                        if (row < gameMatrix.length - 1 && (isWall != (gameMatrix[row + 1][col] == 1))) {
                            g.drawLine(x, y + MOVE_STEP, x + MOVE_STEP, y + MOVE_STEP);
                        }
                        // Check the left boundary
                        if (col > 0 && (isWall != (gameMatrix[row][col - 1] == 1))) {
                            g.drawLine(x, y, x, y + MOVE_STEP);
                        }
                        // Check the right boundary
                        if (col < gameMatrix[row].length - 1 && (isWall != (gameMatrix[row][col + 1] == 1))) {
                            g.drawLine(x + MOVE_STEP, y, x + MOVE_STEP, y + MOVE_STEP);
                        }
                    }
                }
            }
        };

        String hintText = "What rewards do you get from sneaking a bite?";
        String scaredText = "Did the ghost just get scared?";

        // Create top panel with absolute layout
        JPanel topPanel = new JPanel(null); // Use absolute layout
        topPanel.setBackground(Color.BLACK);
        topPanel.setBounds(0, 0, 660, PANEL_OFFSET);

        // Fruit counter label - left side
        fruitCounterLabel = new JLabel("Fruits: " + collectedFruits);
        fruitCounterLabel.setFont(new Font("Arial", Font.BOLD, 16));
        fruitCounterLabel.setForeground(Color.YELLOW);
        fruitCounterLabel.setBounds(20, 10, 150, 20);

        // Hint label - center
        hintLabel = new JLabel(hintText, SwingConstants.CENTER);
        hintLabel.setFont(new Font("Arial", Font.BOLD, 16));
        hintLabel.setForeground(Color.WHITE);
        hintLabel.setBounds(180, 10, 300, 20);

        // Lives label - right side
        livesLabel = new JLabel("Lives: " + playerLives);
        livesLabel.setFont(new Font("Arial", Font.BOLD, 16));
        livesLabel.setForeground(Color.YELLOW);
        livesLabel.setBounds(500, 10, 80, 20);

        // Lives icon - far right
        JLabel livesIcon = new JLabel(loadImageIcon(images.get("Life")[0]));
        livesIcon.setBounds(580, 8, 24, 24);

        // Add all components to the top panel
        topPanel.add(fruitCounterLabel);
        topPanel.add(hintLabel);
        topPanel.add(livesLabel);
        topPanel.add(livesIcon);

        // Add the top panel to the game panel
        gamePanel.add(topPanel);

        // Add panel to the window
        frame.add(gamePanel);
        gamePanel.setLayout(null);
        frame.add(gamePanel);

        // Image display JLabel
        playerImageLabel = new JLabel(loadImageIcon(images.get(playerDirection.name())[playerImageIndex]));
        playerImageLabel.setBounds(playerPositionY * MOVE_STEP, playerPositionX * MOVE_STEP + PANEL_OFFSET, 22, 22);
        gamePanel.add(playerImageLabel);

        // Add keyboard listener
        frame.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                long currentTime = System.currentTimeMillis();
                if (currentTime - lastMoveTimestamp < MOVE_DELAY) {
                    return;
                }
                lastMoveTimestamp = currentTime;

                int keyCode = e.getKeyCode();
                int newRow = playerPositionX;
                int newCol = playerPositionY;

                switch (keyCode) {
                    case KeyEvent.VK_UP:
                        playerDirection = Direction.UP;
                        if (newRow >= 1) {
                            newRow--;
                        }
                        break;
                    case KeyEvent.VK_DOWN:
                        playerDirection = Direction.DOWN;
                        if (newRow < gameMatrix.length - 1) {
                            newRow++;
                        }
                        break;
                    case KeyEvent.VK_LEFT:
                        playerDirection = Direction.LEFT;
                        if (newCol >= 1) {
                            newCol--;
                        }
                        break;
                    case KeyEvent.VK_RIGHT:
                        playerDirection = Direction.RIGHT;
                        if (newCol < gameMatrix[0].length - 1) {
                            newCol++;
                        }
                        break;
                }

                if (gameMatrix[newRow][newCol] == 1) {
                    newRow = playerPositionX;
                    newCol = playerPositionY;
                }

                if (gameMatrix[newRow][newCol] == 2) {
                    totalFruitCount--;
                    if (totalFruitCount == 0) {
                        randomlyChangeZeroToTwo();
                        totalFruitCount++;
                    }
                    gameMatrix[newRow][newCol] = 0;
                    for (Ghost ghost : ghostList) {
                        ghost.setPaused(true);
                        ghost.setPauseStartTime(System.currentTimeMillis());
                    }
                    collectedFruits++;
                    hintLabel.setText(scaredText);
                    fruitCounterLabel.setText(String.format("Fruits collected: %d", collectedFruits));
                }

                if (gameMatrix[newRow][newCol] == 5) {
                    // If it's the left portal
                    if (newCol == 0) {
                        newCol = gameMatrix[0].length - 1; // Teleport to the right
                    }
                    // If it's the right portal
                    else if (newCol == gameMatrix[0].length - 1) {
                        newCol = 0; // Teleport to the left
                    }
                }

                if (newCol < gameMatrix[0].length) {
                    gameInstance.updatePlayerPosition(newRow, newCol);
                }

                playerImageIndex = 0;
                playerImageLabel.setIcon(loadImageIcon(images.get(playerDirection.name())[playerImageIndex]));

                for (Ghost ghost : ghostList) {
                    if (ghost.getRow() == playerPositionX && ghost.getCol() == playerPositionY) {
                        if ("Scared".equals(ghost.getStatus())) {
                            // If the ghost is scared, the ghost dies
                            ghost.setKilled(true); // Set the ghost to dead state
                            gameMatrix[ghost.getRow()][ghost.getCol()] = 0; // Clear the ghost's position
                            ghost.setRow(3);
                            ghost.setCol(4);
                            totalGhostCount--; // Decrease the ghost count
                            System.out.println(totalGhostCount);
                            if (totalGhostCount == 0) {
                                if (isFourthLevel) {
                                    isVictory = true;
                                    gameOver();
                                } else if (isThirdLevel) {
                                    isFourthLevel = true;
                                    reinitializeGameThirdLevel();
                                } else if (isSecondLevel) {
                                    isThirdLevel = true;
                                    reinitializeGameThirdLevel();
                                } else {
                                    isSecondLevel = true;
                                    reinitializeGameSecondLevel();
                                }
                            }
                            hintLabel.setText("Going completely wild!");
                            MOVE_DELAY = 100;
                            break; // Only handle the current ghost
                        } else {
                            // Otherwise, the player dies
                            playerLives--; // Decrease player's life by 1
                            if (playerLives == 0) {
                                gameOver(); // Game over
                            }
                            livesLabel.setText(String.format("Lives remaining: %d", playerLives)); // Update life
                                                                                                   // display

                            // Revive the player to the specified position
                            gameMatrix[playerPositionX][playerPositionY] = 0; // Clear the player's current position
                            playerPositionX = playerRebirthX; // Player's revival position
                            playerPositionY = playerRebirthY; // Player's revival position
                            gameMatrix[playerPositionX][playerPositionY] = 3; // Update player's position

                            playerImageLabel.setBounds(playerPositionY * MOVE_STEP,
                                    playerPositionX * MOVE_STEP + PANEL_OFFSET,
                                    MOVE_STEP, MOVE_STEP);

                            hintLabel.setText("Caught you! Naughty one");
                        }
                        break;
                    }
                }
            }
        });

        // Timer: switch the current direction's image every 0.5 seconds
        Timer timer = new Timer(500, e -> {
            playerImageIndex = (playerImageIndex + 1) % 3;
            playerImageLabel.setIcon(loadImageIcon(images.get(playerDirection.name())[playerImageIndex]));

            if (totalGhostCount > 0) {
                moveGhosts(ghostList);
            } else {
                gameOver();
            }

            gamePanel.repaint();
        });
        timer.start();
        // Window
        frame.setFocusable(true);
        frame.setVisible(true);
    }

    public static void reinitializeGameSecondLevel() {
        final int INITIAL_PLAYER_ROW = 1;
        final int INITIAL_PLAYER_COL = 1;
        final int INITIAL_GHOST_ROW = 3;
        final int INITIAL_GHOST_COL = 3;
        final int GHOST_OFFSET = 7;
        final int FRUIT_COUNT = 10;

        hintLabel.setText("Next level, increased challenge");
        int[][] newPattern = {
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
                { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0 },
                { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 },
                { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0 }
        };
        initializeMatrix(gameMatrix, newPattern);

        resetPlayerPosition(INITIAL_PLAYER_ROW, INITIAL_PLAYER_COL);
        resetGhostPositions(INITIAL_GHOST_ROW, INITIAL_GHOST_COL, GHOST_OFFSET);
        generateFruits(FRUIT_COUNT);

        updateUI();
        resetPlayerImage();
        gamePanel.repaint();
    }

    public static void reinitializeGameThirdLevel() {
        final int INITIAL_PLAYER_ROW = 14;
        final int INITIAL_PLAYER_COL = 14;
        final int GHOST_COUNT = 8;
        final int FRUIT_COUNT = 25;

        // Important: set the total number of ghosts
        totalGhostCount = GHOST_COUNT;

        hintLabel.setText("Third level: Battle Royale! Survive if you can!");

        // Clear the map and create an open field
        for (int i = 0; i < MATRIX_ROWS; i++) {
            for (int j = 0; j < MATRIX_COLS; j++) {
                gameMatrix[i][j] = 0;
            }
        }

        // Set walls only at the edges
        for (int i = 0; i < MATRIX_ROWS; i++) {
            gameMatrix[i][0] = 1;
            gameMatrix[i][MATRIX_COLS - 1] = 1;
        }
        for (int j = 0; j < MATRIX_COLS; j++) {
            gameMatrix[0][j] = 1;
            gameMatrix[MATRIX_ROWS - 1][j] = 1;
        }

        // Randomly add some scattered walls as cover
        Random random = new Random();
        int obstacleCount = 20; // Number of obstacles
        for (int i = 0; i < obstacleCount; i++) {
            int row = random.nextInt(MATRIX_ROWS - 2) + 1;
            int col = random.nextInt(MATRIX_COLS - 2) + 1;
            // Ensure it doesn't block the player's initial position
            if (Math.abs(row - INITIAL_PLAYER_ROW) > 2 || Math.abs(col - INITIAL_PLAYER_COL) > 2) {
                gameMatrix[row][col] = 1;
            }
        }

        // Reset player position
        resetPlayerPosition(INITIAL_PLAYER_ROW, INITIAL_PLAYER_COL);

        // Clear and regenerate ghosts, all ghosts use the same appearance
        ghostList.clear();
        for (int i = 0; i < GHOST_COUNT; i++) {
            int ghostRow, ghostCol;
            do {
                ghostRow = random.nextInt(MATRIX_ROWS - 2) + 1;
                ghostCol = random.nextInt(MATRIX_COLS - 2) + 1;
            } while (gameMatrix[ghostRow][ghostCol] != 0 ||
                    (Math.abs(ghostRow - INITIAL_PLAYER_ROW) < 3 &&
                            Math.abs(ghostCol - INITIAL_PLAYER_COL) < 3));

            Ghost ghost = new Ghost(ghostRow, ghostCol);
            ghost.setStatus("Ghost1"); // All ghosts use the same appearance
            ghostList.add(ghost);
            gameMatrix[ghostRow][ghostCol] = 4;
        }

        // Randomly distribute fruits
        totalFruitCount = 0;
        for (int i = 0; i < FRUIT_COUNT; i++) {
            randomlyChangeZeroToTwo();
            totalFruitCount++;
        }

        // Increase game difficulty
        MOVE_DELAY = 100; // Speed up movement

        // Update UI
        updateUI();
        resetPlayerImage();
        gamePanel.repaint();
    }

    private static void resetPlayerPosition(int row, int col) {
        playerPositionX = row;
        playerPositionY = col;
        gameMatrix[playerPositionX][playerPositionY] = 3;
    }

    private static void resetGhostPositions(int initialRow, int initialCol, int offset) {
        totalGhostCount = 0;
        for (Ghost ghost : ghostList) {
            ghost.setKilled(false);
            ghost.setStatus("Ghost1");
            ghost.setRow(initialRow);
            ghost.setCol(initialCol);
            gameMatrix[initialRow][initialCol] = 4;
            initialRow += offset;
            initialCol += offset;
        }
        totalGhostCount = ghostList.size();
    }

    private static void generateFruits(int count) {
        totalFruitCount = 0;
        for (int i = 0; i < count; i++) {
            randomlyChangeZeroToTwo();
            totalFruitCount++;
        }
    }

    private static void updateUI() {
        hintLabel.setText("What rewards do you get from sneaking a bite?");
        livesLabel.setText(String.format("Lives remaining: %d", playerLives));
        fruitCounterLabel.setText(String.format("Fruits collected: %d", collectedFruits));
    }

    private static void resetPlayerImage() {
        playerDirection = Direction.UP;
        playerImageIndex = 0;
        playerImageLabel.setBounds(playerPositionY * MOVE_STEP, playerPositionX * MOVE_STEP + PANEL_OFFSET, MOVE_STEP,
                MOVE_STEP);
    }

    private void updatePlayerPosition(int newRow, int newCol) {
        gameMatrix[playerPositionX][playerPositionY] = 0;
        playerPositionX = newRow;
        playerPositionY = newCol;
        gameMatrix[playerPositionX][playerPositionY] = 3;
        playerImageLabel.setBounds(playerPositionY * MOVE_STEP, playerPositionX * MOVE_STEP + PANEL_OFFSET, MOVE_STEP,
                MOVE_STEP);
        gamePanel.repaint();
    }

    public enum GhostStatus {
        GHOST1, SCARED
    }

    public static void main(String[] args) {
        startGame();
    }

    private static ImageIcon loadImageIcon(String resourcePath) {
        return new ImageIcon(PacMan.class.getResource(resourcePath));
    }
}
