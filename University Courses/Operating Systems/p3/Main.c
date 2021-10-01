code Main

  -- OS Class: Project 3
  --
  -- <SAEED HEDAYATIAN>
  --

-----------------------------  Main  ---------------------------------

  function main ()
      InitializeScheduler ()
      -----  Uncomment any one of the following to perform the desired test  -----
      -- SleepingBarber ()
      GamingParlor ()

      ThreadFinish ()
    endFunction

-----------------------------  Sleeping Barber  ---------------------------------

  -- This code is an implementation of a solution for the Sleeping Barber problem

  enum IDLE, ENTER, SIT, BEGIN, FINISH, LEAVE, START, END, WORKING
  const
    CHAIRS = 5
    CUSTOMERS = 10

  var
    customersSem, barbersSem, mutex, StartSem, FinishSem: Semaphore
    waiting: int
    threadArray: array [CUSTOMERS + 1] of Thread = new array of Thread {CUSTOMERS + 1 of new Thread } -- threadArray[0] is the barber. The rest are customers.
    status: array [CUSTOMERS + 1] of int

  function SleepingBarber ()
    var
      j: int

      waiting = 0 -- Number of customers waiting
      status = new array of int {CUSTOMERS + 1 of IDLE}

      -- Create semaphores
      customersSem = new Semaphore
      barbersSem = new Semaphore
      mutex = new Semaphore
      StartSem = new Semaphore
      FinishSem = new Semaphore
      -- Initialize semaphores
      customersSem.Init (0)
      barbersSem.Init (0)
      mutex.Init (1)
      StartSem.Init (0)
      FinishSem.Init (0)

      -- Initialize threads
      threadArray[0].Init ("Barber")
      threadArray[0].Fork (Barber, 0)

      for j = 1 to CUSTOMERS by 1
        threadArray[j].Init ("Customer")
        threadArray[j].Fork (Customer, j)
      endFor

     endFunction

  -- This function implements the barber's bahaviour
  function Barber (id: int)
    while true 
      customersSem.Down () -- wait until a customer signals
      mutex.Down ()
      waiting = waiting - 1
      barbersSem.Up () -- signal(awaken) one of the waiting customers

      status[0] = START
      PrintAllStatus () --printing
      status[0] = WORKING
      mutex.Up ()

      CutHair ()
      -------------------------------------------Printing
      mutex.Down ()
      status[0] = END
      PrintAllStatus ()
      status[0] = IDLE
      mutex.Up ()
      -------------------------------------------
    endWhile
  endFunction

  -- This function implements the customers' behaviour
  -- Each customer gets id haircuts and then terminates
  -- id is also used to identify a customer.
  function Customer (id: int)
    var
      i: int

    for i = 1 to id by 1
      WasteTime(id%7 + 2) -- This is done to prevent all customers coming in at once
      mutex.Down ()

      status[id] = ENTER
      PrintAllStatus () --printing

      if waiting < CHAIRS
        waiting = waiting + 1
        status[id] = SIT
        PrintAllStatus () --printing
        customersSem.Up ()
        mutex.Up ()
        barbersSem.Down () -- wait for barber to become available

        -------------------------------------------Printing
        mutex.Down ()
        status[id] = BEGIN
        PrintAllStatus ()
        status[id] = WORKING
        mutex.Up ()
        -------------------------------------------

        GetHaircut ()

        -------------------------------------------Printing
        mutex.Down ()
        status[id] = FINISH
        PrintAllStatus ()
        status [id] = LEAVE
        PrintAllStatus ()
        status [id] = IDLE
        mutex.Up ()
        -------------------------------------------

      else
        -- waiting room is full!
        status [id] = LEAVE
        PrintAllStatus () --printing
        status[id] = IDLE
        mutex.Up ()
      endIf
    endFor
  endFunction

  -- This function is called be the barber
  function CutHair ()
    StartSem.Up() -- signal the active customer that he is getting a haircut
    WasteTime(5)
    FinishSem.Down() -- wait unitl the customer gets up!
  endFunction

  function GetHaircut ()
    StartSem.Down() -- wait for the barber to arrive!
    WasteTime(5)
    FinishSem.Up() -- signal the barber that you are done
  endFunction

  -- This function loops t*1000 times and exits
  function WasteTime (t: int)
    var
      i, x: int = 0

    for i = 1 to 1000*t by 1
      x = x + 1
    endFor
  endFunction

  function PrintAllStatus ()
    var
      i: int

    ---------waiting room status
    for i = 1 to waiting by 1
      print ("X")
    endFor
    for i = waiting + 1 to CHAIRS by 1
      print("-")
    endFor

    print ("  ")

    --customers and barber status
    switch status[0]
      case IDLE:
        print ("      |    ")
        break
      case WORKING:
        print ("***   |    ")
        break
      case END:
        print ("end   |    ")
        break
      case START:
        print ("start |    ")
        break
    endSwitch

    for i = 1 to CUSTOMERS by 1
      if status[i] == WORKING
        print ("  *  ")
      endIf
      switch status [i]
        case ENTER:
          print ("  E  ")
          break
        case SIT:
          print ("  S  ")
          break
        case BEGIN:
          print ("  B  ")
          break
        case IDLE:
          print ("  -  ")
          break
        case FINISH:
          print ("  F  ")
          break
        case LEAVE:
          print ("  L  ")
          break
      endSwitch
    endFor
    nl ()
  endFunction

-----------------------------  Gaming Parlor  ---------------------------------

  -- This code is an implementation of a solution for the Gaming Parlor problem
  const
    PLAYERS = 8

  var
    threadArray2: array [PLAYERS] of Thread = new array of Thread {PLAYERS of new Thread } -- these are threads that simulate the players
    pm: ParlorMonitor

  function GamingParlor ()
    -- Initialize ParlorMonitor
    pm = new ParlorMonitor
    pm.Init ()

    -- Initialize threads
    threadArray2[0].Init ("A")
    threadArray2[0].Fork (Play, 4)

    threadArray2[1].Init ("B")
    threadArray2[1].Fork (Play, 4)

    threadArray2[2].Init ("C")
    threadArray2[2].Fork (Play, 5)

    threadArray2[3].Init ("D")
    threadArray2[3].Fork (Play, 5)

    threadArray2[4].Init ("E")
    threadArray2[4].Fork (Play, 2)

    threadArray2[5].Init ("F")
    threadArray2[5].Fork (Play, 2)

    threadArray2[6].Init ("G")
    threadArray2[6].Fork (Play, 1)

    threadArray2[7].Init ("H")
    threadArray2[7].Fork (Play, 1)

     endFunction

  -- This is the function that player threads run
  function Play (count: int)
    var
      i: int
    for i = 1 to 5 by 1
      pm.Acquire (count)
      currentThread.Yield ()
      pm.Release (count)
      currentThread.Yield ()
    endFor
  endFunction

  -- Class definition for the monitor
  class ParlorMonitor
    superclass Object
    fields
      head: Condition
      queue: Condition
      monitorLock: Mutex
      waitingCount: int
      availableDice: int
    methods
      Init ()
      Acquire (count: int)
      Release (count: int)
      Print (str: String, count: int)
  endClass

  -- Monitor's implementation
  behavior ParlorMonitor

    method Init ()
      -- Initialize the conditions
      head = new Condition
      head.Init ()
      queue = new Condition
      queue.Init ()

      -- Initialize monitors lock
      monitorLock = new Mutex
      monitorLock.Init ()

      -- Initialize the variables
      waitingCount = 0
      availableDice = 8
    endMethod

    -- This method is called when someone wants to requests dice.
    -- First, monitorLock must be acquired for mutual exclusion.
    -- Then, if there is already someone waiting, we wait on the queue. Otherwise we wait on head[of the queue].
    method Acquire (count: int)
      monitorLock.Lock()

      self.Print("requests", count)
      waitingCount = waitingCount + 1
      if waitingCount > 1
        queue.Wait (&monitorLock)
      endIf

      -- We shall use a while instead of an if because conditions are Messa-style
      while count > availableDice
        head.Wait (&monitorLock)
      endWhile

      availableDice = availableDice - count
      waitingCount = waitingCount - 1
      self.Print("proceeds with", count)
      queue.Signal(&monitorLock) -- Signal someone in the queue that you are done with your request

      monitorLock.Unlock ()
      endMethod

    method Release (count: int)
      monitorLock.Lock ()

      availableDice = availableDice + count
      self.Print ("releases and adds back" , count)
      head.Signal (&monitorLock)

      monitorLock.Unlock ()
    endMethod

  method Print (str: String, count: int)
    --
    -- This method prints the current thread's name and the arguments.
    -- It also prints the current number of dice available.
    --
    print (currentThread.name)
    print (" ")
    print (str)
    print (" ")
    printInt (count)
    nl ()
    print ("------------------------------Number of dice now available = ")
    printInt (availableDice)
    nl ()
  endMethod

  endBehavior


endCode
