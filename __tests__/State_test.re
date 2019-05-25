open Jest;
open Expect;
open ReasonHooksTestingLibrary.Testing;

describe("useCounter", () => {
  open State;
  open Result;
  let container = renderHook(() => useCounter(0));
  test("counter is 0", () =>
    expect(container->result->current.counter) |> toEqual(0)
  );
  test("counter is 1", () => {
    act(() => container->result->current.set(prev => prev + 1));
    expect(container->result->current.counter) |> toEqual(1);
  });
  test("counter is 2", () => {
    act(() => container->result->current.set(prev => prev + 1));
    expect(container->result->current.counter) |> toEqual(2);
  });
});

describe("useUndo", () => {
  open State;
  open Result;
  let result = renderHook(() => useUndo(0))->result;
  test("(past, present, future) equals ([], 0, [])", () => {
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([], 0, []));
  });
  test("(past, present, future) equals ([0], 1, [])", () => {
    act(() => result->current.set(prev => prev + 1));
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0], 1, []));
  });
  test("(past, present, future) equals ([0, 1], 2, [])", () => {
    act(() => result->current.set(prev => prev + 1));
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0, 1], 2, []));
  });
  test("undo: (past, present, future) equals ([0], 1, [2])", () => {
    act(() => result->current.undo());
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0], 1, [2]));
  });
  test("redo: (past, present, future) equals ([0,1], 2, [])", () => {
    act(() => result->current.redo());
    let current = result->current;
    expect((current.past, current.present, current.future))
    |> toEqual(([0, 1], 2, []));
  });
});