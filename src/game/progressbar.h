/************************************************************************
 *
 * progressbar.h
 * Progress bar class
 *
 ************************************************************************/

#include "window.h"

/**
 * A progress bar displays a number in the range [0, 1] graphically by
 * filling a portion of the window.
 */
class ProgressBar : public Window
{
public:
    /**
     * Constructor. Initially, the progress is set to zero.
     */
    ProgressBar();

    /**
     * Destructor.
     */
    ~ProgressBar();

    /**
     * Set the progress. p should be in the range [0, 1].
     */
    void setProgress(float p);

protected:
    /**
     * Draw the bar.
     */
    virtual void draw(float dt);

private:
    /**
     * The progress. It is in the range [0, 1].
     */
    float progress;
};
