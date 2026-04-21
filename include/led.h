namespace led
{
    /**
     * @brief Turn the status LED on.
     */
    void ledON();

    /**
     * @brief Turn the status LED off.
     */
    void ledOFF();

    /**
     * @brief Blink the status LED a number of times.
     *
     * @param seconds Number of blink cycles to perform.
     */
    void blink(int seconds);

    /**
     * @brief Initialize the status LED pin.
     */
    void initLed();
}
