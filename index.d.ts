
/**
* @param processName  The name of a running process.
* @returns Returns an array of pids.
*/
export function getProcessesByName(processName: string): Promise<number[]>;

/**
* @param processId  A pid.
* @returns Returns the corresponding title.
*/
export function getProcessWindowTitle(processId: number): Promise<string>;

/**
* @param processId  A pid.
* @returns Returns `false` if the method failed.
*/
export function setProcessToForeground(processId: number): Promise<boolean>;