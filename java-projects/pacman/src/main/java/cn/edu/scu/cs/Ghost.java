package cn.edu.scu.cs;

/**
 * Represents a ghost character in the game with position, status, and animation
 * properties.
 */
public class Ghost {
    private int rowPosition; // The row position of the ghost on the grid
    private int columnPosition; // The column position of the ghost on the grid
    private String currentStatus; // The current status of the ghost, e.g., "Ghost1" or "Scared"
    private int animationFrame; // The current animation frame of the ghost
    private boolean paused; // Indicates if the ghost is currently paused
    private long pauseStartTimestamp; // The timestamp when the ghost was paused
    private boolean killed = false; // Indicates if the ghost has been killed

    /**
     * Constructs a new Ghost with specified row and column positions.
     *
     * @param rowPosition    the initial row position of the ghost
     * @param columnPosition the initial column position of the ghost
     */
    public Ghost(int rowPosition, int columnPosition) {
        this.rowPosition = rowPosition;
        this.columnPosition = columnPosition;
        this.currentStatus = "Ghost1";
        this.animationFrame = 0;
        this.paused = false;
    }

    // Getter and Setter methods

    public int getRowPosition() {
        return rowPosition;
    }

    public void setRowPosition(int rowPosition) {
        this.rowPosition = rowPosition;
    }

    public int getColumnPosition() {
        return columnPosition;
    }

    public void setColumnPosition(int columnPosition) {
        this.columnPosition = columnPosition;
    }

    public boolean isKilled() {
        return killed;
    }

    public void setKilled(boolean killed) {
        this.killed = killed;
    }

    public String getCurrentStatus() {
        return currentStatus;
    }

    public void setCurrentStatus(String currentStatus) {
        this.currentStatus = currentStatus;
    }

    public int getAnimationFrame() {
        return animationFrame;
    }

    public void setAnimationFrame(int animationFrame) {
        this.animationFrame = animationFrame;
    }

    public boolean isPaused() {
        return paused;
    }

    public void setPaused(boolean paused) {
        this.paused = paused;
    }

    public long getPauseStartTimestamp() {
        return pauseStartTimestamp;
    }

    public void setPauseStartTimestamp(long pauseStartTimestamp) {
        this.pauseStartTimestamp = pauseStartTimestamp;
    }

    // Additional methods for setting and getting properties

    public void setStatus(String status) {
        this.currentStatus = status;
    }

    public void setCol(int col) {
        this.columnPosition = col;
    }

    public void setRow(int row) {
        this.rowPosition = row;
    }

    public int getMovement() {
        return animationFrame;
    }

    public void setMovement(int movement) {
        this.animationFrame = movement;
    }

    public long getPauseStartTime() {
        return pauseStartTimestamp;
    }

    public int getRow() {
        return rowPosition;
    }

    public int getCol() {
        return columnPosition;
    }

    public String getStatus() {
        return currentStatus;
    }

    public void setPauseStartTime(long pauseStartTime) {
        this.pauseStartTimestamp = pauseStartTime;
    }
}