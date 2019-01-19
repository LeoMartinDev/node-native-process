
/**
* @param processName  The name of a running process.
* @returns Returns `number[]` an array of pids.
*/
export function getProcessesByName(processName: string): Promise<number[]>;

/**
* @param processId  A pid.
* @returns Returns `string` the corresponding title.
*/
export function getProcessWindowTitle(processId: number): Promise<string>;

/**
* @param processId  A pid.
* @returns Returns `boolean` `false` if the method failed.
*/
export function setProcessToForeground(processId: number): Promise<boolean>;


/**
* @returns Returns `number` foreground window's pid.
*/
export function getForegroundWindowPid(): Promise<number>;