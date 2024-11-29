package cn.edu.scu.cs;

public class Ghost {
    private int rowPosition; // Row position of the ghost
    private int columnPosition; // Column position of the ghost
    private String currentStatus; // Status of the ghost ("Ghost1" or "Scared")
    private int animationFrame; // Animation frame of the ghost
    private boolean paused; // Whether the ghost is paused
    private long pauseStartTimestamp; // Pause start time
    private boolean killed = false; // Whether the ghost is killed

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